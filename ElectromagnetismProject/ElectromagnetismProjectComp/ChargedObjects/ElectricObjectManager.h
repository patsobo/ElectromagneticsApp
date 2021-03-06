#pragma once
#include "Sprite/Sprite.h"
#include "ElectricObject.h"
#include "MagneticObject.h"
#include <map>

class ElectricObjectManager {

public:
	ElectricObjectManager(map<Sprite*, ID3D11ShaderResourceView*> textures, XMFLOAT2 size, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize);

	void Update(float timeTotal, float timeDelta);
	void Draw(SpriteBatch* spriteBatch);

	void checkForCreateObject(XMFLOAT2 point);	// Called when box is touched
	void checkForDeleteObject();	// Called when touch is released over box
	vector<ElectricObject*> getElectricObjects();
	void reset();
	vector<MagneticObject*> getMagneticObjects();
	void addObject(ElectricObject* object);	// TEST METHOD

private:
	vector<ElectricObject*> electricObjects;
	vector<MagneticObject*> magneticObjects;
	map<Sprite*, ID3D11ShaderResourceView*> textures;	// Houses all creation boxes (as keys) with their respective proper texture (as values)
	XMFLOAT2 size;
	XMFLOAT2 position;
	Windows::Foundation::Rect* movementBounds;
	XMFLOAT2 boardSize;
};