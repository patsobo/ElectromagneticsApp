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

const float maxStrength = 100;

class VectorBoard {
	public:
		VectorBoard(Sprite* arrow, XMFLOAT2 boardSize);
		
		void Update(float timeTotal, timeDelta, vector<ElectricObject> electricObjects);
		void Draw(SpriteBatch* spriteBatch);
		
	private:
		vector<vector<VectorCell>> board; 
		
		XMFLOAT2 VectorBoard::calculateSum(int i, int j, vector<ElectricObject> electricObjects);
}