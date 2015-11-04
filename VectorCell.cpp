#include "pch.h"

#include "VectorCell.h"
#include <cmath>

using namespace DirectX;

VectorCell::VectorCell(Sprite* arrow, XMFLOAT2 position) {
	this->arrow = arrow;
	this->position = position;
		
	fieldLine = XMFLOAT2(0, 0);
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
	float pi = atan(1) * 4;
	rotation = atan(-1 * fieldLine.y / fieldLine.x);	// In radians; also, it's negative b/c y goes downward as positive (upwards is more intuitive)
	opacity = sqrt(pow(fieldLine.x, 2) + pow(fieldLine.y, 2)) / MAX_STRENGTH;
	if (opacity > 1)
		opacity = 1;
	arrow->setRotation(rotation);
	arrow->setOpacity(opacity);
}
	
void VectorCell::setFieldLine(XMFLOAT2 newFieldLine) { fieldLine = newFieldLine; }