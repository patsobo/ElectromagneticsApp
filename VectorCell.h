#pragma once

#include "SpriteBatch.h"
#include "Sprite.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "Spritesheet.h"

using namespace DirectX;
using namespace std;

const float maxStrength = 100;

class VectorCell {
	public:
		VectorCell(Sprite* arrow, XMFLOAT2 position);
		
		void Update(float timeTotal, float timeDelta);
		void Draw(SpriteBatch* spriteBatch);
		
		void setVector(XMFLOAT2 newVector);
		
	private:
		Sprite* arrow;
		float opacity;
		float rotation;
		XMFLOAT2 vector;
		XMFLOAT2 position;
		
		void updateOpacityRotation();
}