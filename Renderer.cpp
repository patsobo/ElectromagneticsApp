#include "pch.h"
#include "Renderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

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

	m_spriteBatch = unique_ptr<SpriteBatch>(new DirectX::SpriteBatch(m_d3dContext.Get()));

	// Create the arrow
	arrowTexture = nullptr;
	float scale = .1;
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/arrow.dds", nullptr, &arrowTexture, MAXSIZE_T);
	arrow = new Sprite(arrowTexture, XMFLOAT2(600, 457), XMFLOAT2(0, 0), &m_windowBounds, scale);

	XMFLOAT2 boardSize = XMFLOAT2(int(m_windowBounds.Width / 60), int(m_windowBounds.Height / 45.7));
	vectorBoard = new VectorBoard(arrowTexture, boardSize, &m_windowBounds);
}

void Renderer::Update(float timeTotal, float timeDelta)
{
	vector<ElectricObject> electricObjects;
	vectorBoard->Update(timeTotal, timeDelta, electricObjects);
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
	m_spriteBatch->End();
}

void Renderer::HandlePressInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X, currentPoint->RawPosition.Y);
}

void Renderer::HandleReleaseInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X, currentPoint->RawPosition.Y);
	xSwipeCounter = 0;
	ySwipeCounter = 0;
	previousPoint = XMFLOAT2(0, 0);
}

void Renderer::HandleMoveInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X, currentPoint->RawPosition.Y);
	if (abs(xSwipeCounter) > SWIPE) {
		vectorBoard->addField(XMFLOAT2(xSwipeCounter / abs(xSwipeCounter), 0));	// magnitude
		xSwipeCounter = 0;
	}
	if (abs(ySwipeCounter) > SWIPE) {
		vectorBoard->addField(XMFLOAT2(0, ySwipeCounter / abs(ySwipeCounter)));	// magnitude
		ySwipeCounter = 0;
	}

	if (vectorPoint.y < previousPoint.y) {	// You're moving up
		ySwipeCounter++;
	}
	else if (vectorPoint.y > previousPoint.y) {
		ySwipeCounter--;
	}

	if (vectorPoint.x < previousPoint.x) {	// You're moving left
		xSwipeCounter--;
	}
	else if (vectorPoint.x > previousPoint.x) {
		xSwipeCounter++;
	}

	previousPoint = vectorPoint;

}