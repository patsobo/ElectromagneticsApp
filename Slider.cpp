#pragma once

#include "Sprite.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "Slider.h"

using namespace DirectX;
using namespace std;

class Slider {
	Slider::Slider(Sprite* path, Sprite* bar, int numOptions, float lowVal, float highVal) {
		this->path = path;
		this->bar = bar;
		this->numOptions = numOptions;
		this->lowValue = lowVal;
		this->highValue = highVal;
		
		currentDivot = 0;
		value = lowValue;
		bar->setPosition(XMFLOAT2(getDivotPosition() - (bar->size.x / 2), bar->getPosition.y));
	}
	
	void Slider::Update(float timeTotal, float timeDelta) {
		value = calculateValue();
		bar->setPosition(XMFLOAT2(getDivotPosition() - (bar->size.x / 2), bar->getPosition.y));
		
		// Update the sprites
		bar->Update(timeTotal, timeDelta);
		path->Update(timeTotal, timeDelta);
	}
	
	void Slider::Draw(SpriteBatch* spriteBatch) {
		path->Draw(spriteBatch);
		bar->Draw(spriteBatch);
	}

	void Slider::handleTouch(XMFLOAT2 point) {
		currentDivot = calculateDivot(point);
	}
	
	int Slider::calculateValue() {
		return ((highValue - lowValue) / numOptions) * currentDivot;
	}
	
	int Slider::calculateDivot(XMFLOAT2 point) {
		if (point.x >= getDivotPosition() + (path->size.x / (numOptions * 2)) {
			if(currentDivot > numOptions || currentDivot <= 0)
				return currentDivot;
			else return currentDivot + 1;
		}
	}
	
	float Slider::getDivotPosition() {
		return currentDivot*(path->size.x / numOptions) + path->position.x;
	}
	
	float Slider::getValue() {
		return value;
	}
}