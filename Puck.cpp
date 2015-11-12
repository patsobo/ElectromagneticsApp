#include "pch.h"
#include "Puck.h"

Puck::Puck(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize) : 
Sprite(m_Texture, size, position, movementBounds, .1, 0, XMFLOAT2(size.x / 2, size.y / 2))
{
}

void Puck::Update(float timeTotal, float timeDelta, XMFLOAT2 currentField) {
	calculateVelocity(currentField);
	Sprite::Update(timeTotal, timeDelta);	
}

XMFLOAT2 Puck::calculateVelocity(XMFLOAT2 currentField) {
	Velocity.x += currentField.x;
	Velocity.y += currentField.y;
}