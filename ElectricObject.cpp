#include "pch.h"
#include "ElectricObject.h"


// TODO: Make ElectricObject a child of Sprite

ElectricObject::ElectricObject()
{
}

void ElectricObject::isTouched(XMFLOAT2 point) {
	//setPosition(point);
}

vector<vector<XMFLOAT2>> ElectricObject::getGrid() {
	vector<vector<XMFLOAT2>> a;
	vector <XMFLOAT2> b;
	b.push_back(XMFLOAT2(0, 0));
	a.push_back(b);
	return a;
}