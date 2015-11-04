#include "pch.h"
#include "ElectricObject.h"


ElectricObject::ElectricObject()
{
}

vector<vector<XMFLOAT2>> ElectricObject::getGrid() {
	vector<vector<XMFLOAT2>> a;
	vector <XMFLOAT2> b;
	b.push_back(XMFLOAT2(0, 0));
	a.push_back(b);
	return a;
}