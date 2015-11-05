#pragma once
#include "Sprite.h"
class ElectricObject {

public:
	ElectricObject();

	void isTouched(XMFLOAT2 point);
	vector<vector<XMFLOAT2>> getGrid();

private:
};

