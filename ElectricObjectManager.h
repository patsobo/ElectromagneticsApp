#pragma once
#include "Sprite.h"
#include "ElectricObject.h"

static float CHARGE = 1;
static float K = 100000;

class ElectricObjectManager {

public:
	ElectricObjectManager(Sprite* box, ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize);

	void Update(float timeTotal, float timeDelta);
	void Draw(SpriteBatch* spriteBatch);

private:
	vector<ElectricObject*> electricObjects;

	void createObject();	// Called when box is touched
	void deleteObject(ElectricObject* thing);	// Called when touch is released over box
	ID3D11ShaderResourceView *texture;
	XMFLOAT2 size;
	XMFLOAT2 position;
	Windows::Foundation::Rect* movementBounds;
	XMFLOAT2 boardSize;

};