#pragma once

#include "Sprite.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "VectorCell.h"
#include <math>

using namespace DirectX;
using namespace std;

class VectorCell {
	VectorCell::VectorCell(Sprite* arrow, XMFLOAT2 position) {
		this->arrow = arrow;
		this->position = position;
		
		vector = XMFLOAT2(0, 0);
		updateOpacityRotation();				
	}
	
	void VectorCell::Update(float timeTotal, float timeDelta) {
		updateOpacityRotation();
		
		// Update the sprites
		arrow->Update(timeTotal, timeDelta);
	}
	
	void VectorCell::Draw(SpriteBatch* spriteBatch) {
		arrow->Draw(spriteBatch);
	}
	
	void VectorCell::updateOpacityRotation() {
		rotation = math.arctan(vector.y / vector.x) * math.pi / 180;
		opacity = sqrt(pow(vector.x, 2) + pow(vector.y, 2)) / maxStrength;
		if (opacity > 1)
			opacity = 1;
	}
	
	void VectorCell::setVector(XMFLOAT2 newVector) { vector = newVector; }
}