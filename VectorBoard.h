#pragma once

#include "Sprite.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "VectorCell.h"
#include "ElectricObject.h"

using namespace DirectX;
using namespace std;

class VectorBoard {
	public:
		VectorBoard(ID3D11ShaderResourceView* arrowTexture, XMFLOAT2 boardSize, Windows::Foundation::Rect* movementBounds);
		
		void Update(float timeTotal, float timeDelta, vector<ElectricObject> electricObjects);
		void Draw(SpriteBatch* spriteBatch);
		
	private:
		Windows::Foundation::Rect* movementBounds;
		vector<vector<VectorCell*>> board; 
		
		XMFLOAT2 VectorBoard::calculateSum(int i, int j, vector<ElectricObject> electricObjects);
};