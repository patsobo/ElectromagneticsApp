#pragma once
#include "Sprite.h"

static float CHARGE = 1;
static float K = 100000;

class ElectricObject : public Sprite {

public:
	ElectricObject(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize);

	void isTouched(XMFLOAT2 point);
	XMFLOAT2 calculateField(XMFLOAT2 position);

	// Ehh....
	bool isMoving;

private:
	vector<vector<XMFLOAT2>> board;

	void createBoard(XMFLOAT2 boardSize);
};

