#pragma once

#include "Direct3DBase.h"
#include "VectorBoard.h"	// Includes VectorCell.h
#include "Slider.h"
#include "AppState.h"
#include "ElectricObjectManager.h"
#include "Puck.h"
#include <map>

static int SWIPE = 5;

ref class Renderer sealed : public Direct3DBase
{
public:
	Renderer();

	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	
	// Method for updating time-dependent objects.
	void Update(float timeTotal, float timeDelta);

	// For handling touch input.
	void HandlePressInput(Windows::UI::Input::PointerPoint^ currentPoint);	// called when pointer is down, alters state
	void HandleReleaseInput(Windows::UI::Input::PointerPoint^ currentPoint);	// called when pointer is released, alters state
	void HandleMoveInput(Windows::UI::Input::PointerPoint^ currentPoint);
private:
	float scale;	// Scale for the screen (VERY IMPORTANT)
	unique_ptr<SpriteBatch> m_spriteBatch;
	ID3D11ShaderResourceView* arrowTexture;
	Sprite* arrow;
	VectorBoard* vectorBoard;
	ID3D11ShaderResourceView* posChargeTexture;
	ElectricObject* posCharge;
	ID3D11ShaderResourceView* negChargeTexture;
	ElectricObject* negCharge;
	ID3D11ShaderResourceView* chargeBoxTexture;
	ID3D11ShaderResourceView* negChargeBoxTexture;
	Sprite* chargeBox;
	Sprite* negChargeBox;
	ElectricObjectManager* objectManager;
	map<Sprite*, ID3D11ShaderResourceView*> textures;
	Puck* puck;
	ID3D11ShaderResourceView* puckTexture;
	//vector<ElectricObject*> electricObjects;

	bool onSprite(Sprite* thing, XMFLOAT2 point);

	// Test variables
	int xSwipeCounter;
	int ySwipeCounter;
	XMFLOAT2 previousPoint;
};