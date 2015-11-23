#include "pch.h"
#include "MagneticObject.h"


// TODO: Make MagneticObject a child of ElectricObject, and make a ChargeObject

MagneticObject::MagneticObject(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize, float current, float scale) : 
ElectricObject(m_Texture, size, position, movementBounds, boardSize, 1, scale)
{
	this->isMoving = false;
	this->current = current;
	createBoard(boardSize);
}

void MagneticObject::createBoard(XMFLOAT2 boardSize) {

}

void MagneticObject::isTouched(XMFLOAT2 point) {
	Windows::Foundation::Point specPoint = Windows::Foundation::Point(point.x, point.y);
	point.x = position.x;	// keep x position constant.
	//if (getBoundingBox()->Contains(specPoint))
	setPosition(point);
}

XMFLOAT2 MagneticObject::calculateField(XMFLOAT2 point) {
	float y = point.y - position.y;
	float magnitude = M * current / y;	// approximate electric field equation

	return XMFLOAT2(0, magnitude);	// wire in x direction only has b-field in y plane.
}