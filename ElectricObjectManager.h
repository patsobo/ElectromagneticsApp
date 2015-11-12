#pragma once
#include "Sprite.h"
#include "ElectricObject.h"

class ElectricObjectManager {

public:
	ElectricObjectManager(Sprite* box, ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize);

	void Update(float timeTotal, float timeDelta);
	void Draw(SpriteBatch* spriteBatch);

	void createObject();	// Called when box is touched
	void checkForDeleteObject();	// Called when touch is released over box
	Sprite* getCreationBox();	// Get the creation box
	vector<ElectricObject*> getElectricObjects();

private:
	vector<ElectricObject*> electricObjects;

	ID3D11ShaderResourceView *texture;
	XMFLOAT2 size;
	XMFLOAT2 position;
	Windows::Foundation::Rect* movementBounds;
	XMFLOAT2 boardSize;
	Sprite* creationBox;

};