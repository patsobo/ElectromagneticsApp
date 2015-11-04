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
	rotation = atan(fieldLine.y / fieldLine.x) * pi / 180;
	opacity = sqrt(pow(fieldLine.x, 2) + pow(fieldLine.y, 2)) / MAX_STRENGTH;
	if (opacity > 1)
		opacity = 1;
}
	
void VectorCell::setFieldLine(XMFLOAT2 newFieldLine) { fieldLine = newFieldLine; }