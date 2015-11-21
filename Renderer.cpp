#include "pch.h"
#include "Renderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::Graphics::Display;

Renderer::Renderer() {
	previousPoint = XMFLOAT2(0, 0);
	appState = AppState::MainMenu;
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

	// Create the positive charge
	posChargeTexture = nullptr;
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/charge.dds", nullptr, &posChargeTexture, MAXSIZE_T);
	posCharge = new ElectricObject(posChargeTexture, XMFLOAT2(500, 500), XMFLOAT2(100, 100), &m_windowBounds, boardSize, 1, .1);
	chargeBoxTexture = nullptr;
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/charge_box.dds", nullptr, &chargeBoxTexture, MAXSIZE_T);
	chargeBox = new Sprite(chargeBoxTexture, XMFLOAT2(500, 500), XMFLOAT2(m_windowBounds.Width - 100, m_windowBounds.Height - 100), &m_windowBounds, .2);
	textures[chargeBox] = posChargeTexture;

	// Create the negative charge
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/neg_charge.dds", nullptr, &negChargeTexture, MAXSIZE_T);
	negCharge = new ElectricObject(negChargeTexture, XMFLOAT2(500, 500), XMFLOAT2(100, 100), &m_windowBounds, boardSize, -1, .1);
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/neg_charge_box.dds", nullptr, &negChargeBoxTexture, MAXSIZE_T);
	negChargeBox = new Sprite(negChargeBoxTexture, XMFLOAT2(500, 500), XMFLOAT2(m_windowBounds.Width - 200, m_windowBounds.Height - 100), &m_windowBounds, .2);
	textures[negChargeBox] = negChargeTexture;

	// Create the wire
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/wire.dds", nullptr, &wireTexture, MAXSIZE_T);
	wire = new MagneticObject(wireTexture, XMFLOAT2(768, 20), XMFLOAT2(m_windowBounds.Width / 2, 500), &m_windowBounds, boardSize, .0001f, 1);
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/wire_box.dds", nullptr, &wireBoxTexture, MAXSIZE_T);
	wireBox = new Sprite(wireBoxTexture, XMFLOAT2(500, 500), XMFLOAT2(m_windowBounds.Width - 300, m_windowBounds.Height - 100), &m_windowBounds, .2);
	textures[wireBox] = wireTexture;

	// Create the charge box and the electric object manager
	objectManager = new ElectricObjectManager(textures, XMFLOAT2(500, 500), &m_windowBounds, boardSize);

	// TEST PURPOSES ONLY
	//objectManager->addObject(wire);

	// Create the puck
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/puck.dds", nullptr, &puckTexture, MAXSIZE_T);
	puckBounds = new Rect(-1 * m_windowBounds.Width, -1 * m_windowBounds.Height, 3 * m_windowBounds.Width, 3 * m_windowBounds.Height);
	puck = new Puck(puckTexture, XMFLOAT2(500, 500), XMFLOAT2(m_windowBounds.Width / 2, m_windowBounds.Height / 2), puckBounds);

	//Create the start button
	float buttonScale = .3;
	XMFLOAT2 sizeOfButton(210, 235);
	XMFLOAT2 positionOfStart(m_windowBounds.Width - sizeOfButton.x*buttonScale - 30, 30);
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/play_button.dds", nullptr, &startButtonTexture, MAXSIZE_T);
	startButton = new Sprite(startButtonTexture, sizeOfButton, positionOfStart, &m_windowBounds, buttonScale);
	//Create the pause button
	sizeOfButton = XMFLOAT2(189, 217);
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/pause_button.dds", nullptr, &pauseButtonTexture, MAXSIZE_T);
	pauseButton = new Sprite(pauseButtonTexture, sizeOfButton, positionOfStart, &m_windowBounds, buttonScale);

	//Create the reset button
	XMFLOAT2 sizeOfReset(248, 210);
	positionOfStart.y += sizeOfButton.y*buttonScale + 30;
	CreateDDSTextureFromFile(m_d3dDevice.Get(), L"Assets/reset_button_2.dds", nullptr, &resetButtonTexture, MAXSIZE_T);
	resetButton = new Sprite(resetButtonTexture, sizeOfReset, positionOfStart, &m_windowBounds, buttonScale);
}

void Renderer::Update(float timeTotal, float timeDelta)
{
	switch (appState) {
	case AppState::MainMenu:
		break;
	case AppState::InGameSetup:
		objectManager->Update(timeTotal, timeDelta);
		vectorBoard->Update(timeTotal, timeDelta, objectManager->getElectricObjects());
		startButton->Update(timeTotal, timeDelta);
		resetButton->Update(timeTotal, timeDelta);
		break;
	case AppState::InGameRunning:
		vectorBoard->Update(timeTotal, timeDelta, objectManager->getElectricObjects());
		puck->Update(timeTotal, timeDelta, vectorBoard->getClosestField(puck->getPosition()));
		objectManager->Update(timeTotal, timeDelta);
		pauseButton->Update(timeTotal, timeDelta);
		resetButton->Update(timeTotal, timeDelta);
		break;
	default:
		break;
	}

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
	switch (appState) {
	case AppState::MainMenu:
		break;
	case AppState::InGameSetup:
		vectorBoard->Draw(m_spriteBatch.get());
		puck->Draw(m_spriteBatch.get());
		objectManager->Draw(m_spriteBatch.get());
		resetButton->Draw(m_spriteBatch.get());
		startButton->Draw(m_spriteBatch.get());
		break;
	case AppState::InGameRunning:
		vectorBoard->Draw(m_spriteBatch.get());
		puck->Draw(m_spriteBatch.get());
		objectManager->Draw(m_spriteBatch.get());
		resetButton->Draw(m_spriteBatch.get());
		pauseButton->Draw(m_spriteBatch.get());
		break;
	default:
		break;
	}
	
	m_spriteBatch->End();
}

void Renderer::HandlePressInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X * scale, currentPoint->RawPosition.Y * scale);

	switch (appState) {
	case AppState::InGameSetup:
		if (onSprite(startButton, vectorPoint)) {	// start button is pressed
			appState = AppState::InGameRunning;
		}
		if (onSprite(resetButton, vectorPoint)) {	// start button is pressed
			reset();
		}

		for (ElectricObject* thing : objectManager->getElectricObjects()) {
			if (onSprite(thing, vectorPoint)) {
				thing->isTouched(vectorPoint);
				thing->isMoving = true;
				break;	// break because we only want one charge to be moving
			}
		}

		// Check for if an object should be created.
		objectManager->checkForCreateObject(vectorPoint);
		break;
	case AppState::InGameRunning:
		for (ElectricObject* thing : objectManager->getElectricObjects()) {
			if (onSprite(thing, vectorPoint)) {
				thing->isTouched(vectorPoint);
				thing->isMoving = true;
				break;	// break because we only want one charge to be moving
			}
		}

		// Check if should pause game.
		if (onSprite(pauseButton, vectorPoint)) {
			appState = AppState::InGameSetup;
		}

		// Check for if an object should be created.
		objectManager->checkForCreateObject(vectorPoint);
		if (onSprite(resetButton, vectorPoint)) {	// start button is pressed
			reset();
			appState = AppState::InGameSetup;
		}
		break;
	default:
		break;
	}


}

void Renderer::HandleReleaseInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X * scale, currentPoint->RawPosition.Y * scale);

	switch (appState) {
	case AppState::MainMenu:
		appState = AppState::InGameSetup;
		break;
	case AppState::InGameSetup:
		previousPoint = XMFLOAT2(0, 0);
		for (ElectricObject* thing : objectManager->getElectricObjects()) {
			if (thing->isMoving) {
				thing->isMoving = false;
			}
		}

		// If you've dragged an object into the box
		objectManager->checkForDeleteObject();
		break;
	case AppState::InGameRunning:	// same as the set up
		previousPoint = XMFLOAT2(0, 0);
		for (ElectricObject* thing : objectManager->getElectricObjects()) {
			if (thing->isMoving) {
				thing->isMoving = false;
			}
		}

		// If you've dragged an object into the box
		objectManager->checkForDeleteObject();
		break;
	default:
		break;
	}


}

void Renderer::HandleMoveInput(Windows::UI::Input::PointerPoint^ currentPoint)
{
	XMFLOAT2 vectorPoint = XMFLOAT2(currentPoint->RawPosition.X * scale, currentPoint->RawPosition.Y * scale);
	bool noneIsMoving = true;

	switch (appState) {
	case AppState::InGameSetup:
		for (ElectricObject* thing : objectManager->getElectricObjects()) {
			//if (onSprite(thing, vectorPoint) && thing->isMoving) {	// code for allowing multi-touch
			//	thing->isTouched(vectorPoint);
			//	noneIsMoving = false;
			//}
			if (thing->isMoving) {	// code for allowing fast movement
				thing->isTouched(vectorPoint);
				noneIsMoving = false;
			}
		}
		if (noneIsMoving) {	// Made for specific case where, if you haven't selected any charge when you were moving, the first you move over becomes the charge that moves.
			for (ElectricObject* thing : objectManager->getElectricObjects()) {
				if (onSprite(thing, vectorPoint)) {
					thing->isTouched(vectorPoint);
					thing->isMoving = true;
					break;
				}
			}
		}
		break;
	case AppState::InGameRunning:	// either running or setting up
		for (ElectricObject* thing : objectManager->getElectricObjects()) {
			if (onSprite(thing, vectorPoint) && thing->isMoving) {
				thing->isTouched(vectorPoint);
				noneIsMoving = false;
			}
		}
		if (noneIsMoving) {	// Made for specific case where, if you haven't selected any charge when you were moving, the first you move over becomes the charge that moves.
			for (ElectricObject* thing : objectManager->getElectricObjects()) {
				if (onSprite(thing, vectorPoint)) {
					thing->isTouched(vectorPoint);
					thing->isMoving = true;
					break;
				}
			}
		}
		break;
	default:
		break;
	}


}

bool Renderer::onSprite(Sprite* thing, XMFLOAT2 pointer)
{
	Point point = Point(pointer.x, pointer.y);
	Rect box = *thing->getBoundingBox();
	if (thing->getBoundingBox()->Contains(point))
		return true;
	return false;
}

void Renderer::reset() {
	puck->reset();
	objectManager->reset();
}