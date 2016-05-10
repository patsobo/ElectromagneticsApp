#pragma once

#include "Sprite/Sprite.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "VectorCell.h"
#include "ChargedObjects/ElectricObject.h"
#include "ChargedObjects/MagneticObject.h"

using namespace DirectX;
using namespace std;

class VectorBoard {
	public:
		VectorBoard(ID3D11ShaderResourceView* arrowTexture, XMFLOAT2 boardSize, Windows::Foundation::Rect* movementBounds);
		
		void Update(float timeTotal, float timeDelta, vector<ElectricObject*> electricObjects);
		void Draw(SpriteBatch* spriteBatch);
		XMFLOAT2 getClosestField(XMFLOAT2 position, XMFLOAT2 velocity, vector<MagneticObject*> magneticObjects);

		// Test method
		void addField(XMFLOAT2 field);
		
	private:
		Windows::Foundation::Rect* movementBounds;
		vector<vector<VectorCell*>> board; 
		XMFLOAT2 unitLength;

		void calculateSum(vector<ElectricObject*> electricObjects);
		XMFLOAT2 getMagneticSum(vector<MagneticObject*> magneticObjects, XMFLOAT2 position, XMFLOAT2 velocity);
};