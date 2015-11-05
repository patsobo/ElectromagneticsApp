#include "pch.h"
#include "ElectricObject.h"


// TODO: Make ElectricObject a child of Sprite

ElectricObject::ElectricObject(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize) : 
Sprite(m_Texture, size, position, movementBounds, .1, 0, XMFLOAT2(size.x / 2, size.y / 2))
{
	this->isMoving = false;
	createBoard(boardSize);
}

void ElectricObject::createBoard(XMFLOAT2 boardSize) {

}

void ElectricObject::isTouched(XMFLOAT2 point) {
	Windows::Foundation::Point specPoint = Windows::Foundation::Point(point.x, point.y);
	if (getBoundingBox()->Contains(specPoint))
		setPosition(point);
}

XMFLOAT2 ElectricObject::calculateField(XMFLOAT2 point) {
	float x = point.x - position.x;
	float y = point.y - position.y;
	float distance = sqrt(pow(abs(y), 2) + pow(abs(x), 2));
	float magnitude = K * CHARGE / pow(distance, 2);	// approximate electric field equation

	return XMFLOAT2(magnitude * x / distance, -1 * magnitude* y / distance);
}