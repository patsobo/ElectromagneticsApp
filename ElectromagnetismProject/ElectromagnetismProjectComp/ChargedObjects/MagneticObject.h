#pragma once
#include "ElectricObject.h"

static float M = 100000*140;

class MagneticObject : public ElectricObject {

public:
	MagneticObject(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize, float current, float scale);

	void isTouched(XMFLOAT2 point);
	
	// Overloaded method
	XMFLOAT2 calculateField(XMFLOAT2 position, XMFLOAT2 velocity);

	// Ehh....
	bool isMoving;

private:
	vector<vector<XMFLOAT2>> board;
	float current; // current should be on the order of milliamps to compensate for the much larger M value (M ~ 140x greater than K*Q);

	void createBoard(XMFLOAT2 boardSize);
};
