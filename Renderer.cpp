#include "pch.h"
#include "Renderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::Graphics::Display;

Renderer::Renderer() {
	xSwipeCounter = 0;
	ySwipeCounter = 0;
	previousPoint = XMFLOAT2(0, 0);
}

void Renderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();
}

void Renderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();

	scale = DisplayProperties::LogicalDpi / 96.0f;
	m_windowBounds.Height *= scale;
	m_windowBounds.Width *= scale;

	float localScale;

	m_spriteBatch = unique_ptr<SpriteBatch>(new DirectX::SpriteBatch(m_d3dContext.Get()));

	// Create the arrow
	arrowTexture = nullptr;
	localScale = .1;
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/arrow.dds", nullptr, &arrowTexture, MAXSIZE_T);
	arrow = new Sprite(arrowTexture, XMFLOAT2(600, 457), XMFLOAT2(0, 0), &m_windowBounds, localScale);

	// Create the vector board
	XMFLOAT2 boardSize = XMFLOAT2(int(m_windowBounds.Width / 60), int(m_windowBounds.Height / 60));
	vectorBoard = new VectorBoard(arrowTexture, boardSize, &m_windowBounds);

	// Create the charge
	chargeTexture = nullptr;
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/charge.dds", nullptr, &chargeTexture, MAXSIZE_T);
	charge = new ElectricObject(chargeTexture, XMFLOAT2(500, 500), XMFLOAT2(100, 100), &m_windowBounds, boardSize);
	electricObjects.push_back(charge);
	charge = new ElectricObject(chargeTexture, XMFLOAT2(500, 500), XMFLOAT2(400, 400), &m_windowBounds, boardSize);
	electricObjects.push_back(charge);
}

void Renderer::Update(float timeTotal, float timeDelta)
{
	vectorBoard->Update(timeTotal, timeDelta, electricObjects);
	for (ElectricObject* thing : electricObjects)
		thing->Update(timeTotal, timeDelta);
}

void Renderer::Render()
{
	// Background color
	const float bg_color[] = { 245.0f / 255.0f, 241.0 / 255.0f, 196.0f / 255.0f, 1.000f };
	m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(),
		bg_color
		);

	// Necessary for proper rendering
	m_d3dContext->ClearDepthStencilView(
		m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	m_d3dContext->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		m_depthStencilView.Get()
		);

	// Where my sprites will be drawn
	m_spriteBatch->Begin();
	vectorBoard->Draw(m_spriteBatch.get());
	for (ElectricObject* thing : electricObjects)
		thing->Draw(m_spriteBatch.get());
	m_spriteBatch->End();
}

void Renderer::HandlePressInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X * scale, currentPoint->RawPosition.Y * scale);
	for (ElectricObject* thing : electricObjects) {
		if (onSprite(thing, vectorPoint)) {
			thing->isTouched(vectorPoint);
			thing->isMoving = true;
			break;	// break because we only want one charge to be moving
		}
	}
}

void Renderer::HandleReleaseInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X * scale, currentPoint->RawPosition.Y * scale);
	xSwipeCounter = 0;
	ySwipeCounter = 0;
	previousPoint = XMFLOAT2(0, 0);

	for (ElectricObject* thing : electricObjects) {
		if (thing->isMoving) {
			thing->isMoving = false;
		}
	}
}

void Renderer::HandleMoveInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	bool noneIsMoving = true;
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X * scale, currentPoint->RawPosition.Y * scale);
	for (ElectricObject* thing : electricObjects) {
		if (onSprite(thing, vectorPoint) && thing->isMoving) {
			thing->isTouched(vectorPoint);
			noneIsMoving = false;
		}
	}
	if (noneIsMoving) {	// Made for specific case where, if you haven't selected any charge when you were moving, the first you move over becomes the charge that moves.
		for (ElectricObject* thing : electricObjects) {
			if (onSprite(thing, vectorPoint)) {
				thing->isTouched(vectorPoint);
				thing->isMoving = true;
				break;
		}
		}
	}

	//if (abs(xSwipeCounter) > SWIPE) {
	//	vectorBoard->addField(XMFLOAT2(xSwipeCounter / abs(xSwipeCounter), 0));	// magnitude
	//	xSwipeCounter = 0;
	//}
	//if (abs(ySwipeCounter) > SWIPE) {
	//	vectorBoard->addField(XMFLOAT2(0, ySwipeCounter / abs(ySwipeCounter)));	// magnitude
	//	ySwipeCounter = 0;
	//}

	//if (vectorPoint.y < previousPoint.y) {	// You're moving up
	//	ySwipeCounter++;
	//}
	//else if (vectorPoint.y > previousPoint.y) {
	//	ySwipeCounter--;
	//}

	//if (vectorPoint.x < previousPoint.x) {	// You're moving left
	//	xSwipeCounter--;
	//}
	//else if (vectorPoint.x > previousPoint.x) {
	//	xSwipeCounter++;
	//}

	//previousPoint = vectorPoint;

}

bool Renderer::onSprite(Sprite* thing, XMFLOAT2 pointer)
{
	Point point = Point(pointer.x, pointer.y);
	Rect box = *thing->getBoundingBox();
	if (thing->getBoundingBox()->Contains(point))
		return true;
	return false;
}