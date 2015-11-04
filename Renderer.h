#pragma once

#include "Direct3DBase.h"
#include "VectorBoard.h"	// Includes VectorCell.h
#include "Slider.h"

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

private:
	ID3D11ShaderResourceView* arrowTexture;
	Sprite* arrow;
	VectorBoard vectorBoard;
};