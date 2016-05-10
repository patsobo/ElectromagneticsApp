#include "pch.h"
#include "MagneticObject.h"
#include <math.h>

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

XMFLOAT2 MagneticObject::calculateField(XMFLOAT2 point, XMFLOAT2 velocity) {
	float d = point.y - position.y;	// radius (distance)
	d == 0 ? d = .1 : d = d;
	float magnitude = M * current / d;	// approximate electric field equation
	
	// normalize velocity
	float tempMag = pow(velocity.x, 2) + pow(velocity.y, 2);
	if (tempMag == 0)
		return XMFLOAT2(0, 0);
	velocity.x /= tempMag;
	velocity.y /= tempMag;

	float x = velocity.x;
	float y = velocity.y;
	float temp;

	// if negative, rotate 90 degrees clockwise (by flipping the x and y)
	// this is basically a cross product
	if (d < 0) {
		temp = x;
		x = y;
		y = -1 * temp;
	}
	else if (d > 0) { // else rotate 90 degrees counterclockwise
		temp = y;
		y = x;
		x = -1 * temp;
	}	

	return XMFLOAT2(x*magnitude, y*magnitude);	// wire in x direction only has b-field in y plane.
}