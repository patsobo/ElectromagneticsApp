/*
spritesheet.h

For 2D game animation.

Header file for spritesheet class, which handles parsing of sprite sheets
for the sprite class to use.

authors: Patrick Sobolewski and Nolan Sneed
*/
#pragma once

#include "SpriteBatch.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>

using namespace DirectX;
using namespace std;

class Spritesheet {
	friend class Sprite;
public:
	// Default constructor
	Spritesheet();
	Spritesheet(XMFLOAT2 size);
	Spritesheet(vector<XMFLOAT2> sizes, int numOfAnimations, vector<int> numOfFrames, int totalWidth);

	// Called when event is detected
	// Determines currentPosition, currentHeight, currentWidth
	// animationState is which animation is in focus; currentFrame is which frame within that animation.
	void Update(int animationState, int currentFrame);

protected:
	// variables for the Sprite class to use
	int currentAnimation;
	XMFLOAT2 currentPosition;
	XMFLOAT2 currentSize;

	// numOfFrames holds the number of frames in each animation, in order
	vector<int> numOfFrames;

private:
	// local variables
	// numOfAnimations holds the total number of animations
	// positions gives the starting x and y positions of each animation
	// sizes gives the width and height of each animation
	int numOfAnimations;
	vector<XMFLOAT2> positions;
	vector<XMFLOAT2> sizes;

	// Creates the "positions" Vector2 from the "sizes" Vector2
	void Parse(vector<XMFLOAT2> sizes, int numOfAnimations, vector<int> numOfFrames, int totalWidth);
};