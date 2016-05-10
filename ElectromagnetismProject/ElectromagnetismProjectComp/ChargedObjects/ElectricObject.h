#pragma once
#include "Sprite/Sprite.h"

static float K = 100000;

class ElectricObject : public Sprite {

public:
	ElectricObject(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize, int charge, float scale);

	virtual void isTouched(XMFLOAT2 point);
	virtual XMFLOAT2 calculateField(XMFLOAT2 position);

	// Ehh....
	bool isMoving;

private:
	vector<vector<XMFLOAT2>> board;
	int charge; 

	void createBoard(XMFLOAT2 boardSize);
};

