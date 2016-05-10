#pragma once

#include "SpriteBatch.h"
#include "Sprite/Sprite.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "../Sprite/Spritesheet.h"

using namespace DirectX;
using namespace std;

class Slider {
	public:
		Slider(Sprite* path, Sprite* bar, int numOptions, float lowVal=0, float highVal=100);
	
		void Update(float timeTotal, float timeDelta);
		void Draw(SpriteBatch* spriteBatch);
		
		float getValue();
		
	private:
		Sprite* bar;	// The thing you slide
		Sprite* path;	// The thing the bar slides on
		float value;	// The current value of the slider
		int currentDivot;	// The current divot you're on
		int numOptions;	// The number of divots in the slider
		float lowValue;
		float highValue;
		
		void handleTouch(XMFLOAT2 point);
		int calculateValue();
		int calculateDivot(XMFLOAT2 point);
		float getDivotPosition();
		
	//protected: 
};