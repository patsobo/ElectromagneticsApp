#include "pch.h"
#include "Sprite.h"
#include "Spritesheet.h"

#include <vector>
#include "Windows.h"
#include <list>

using namespace DirectX;
using namespace std;

Spritesheet::Spritesheet()
{
	numOfAnimations = 1;
	numOfFrames.push_back(1);
	sizes.push_back(XMFLOAT2(0, 0));

	currentPosition.x = 0;
	currentPosition.y = 0;
	currentSize.x = 0;
	currentSize.y = 0;	// placeholder values (replace with size of screen)
	currentAnimation = 0;

	Parse(sizes, numOfAnimations, numOfFrames, sizes[0].x);
}

Spritesheet::Spritesheet(XMFLOAT2 size)
{
	numOfAnimations = 1;
	numOfFrames.push_back(1);
	sizes.push_back(size);

	currentPosition.x = 0;
	currentPosition.y = 0;
	currentSize.x = size.x;
	currentSize.y = size.y;	// placeholder values (replace with size of screen)
	currentAnimation = 0;

	Parse(sizes, numOfAnimations, numOfFrames, size.x);
}

Spritesheet::Spritesheet(vector<XMFLOAT2> sizes, int numOfAnimations, vector<int> numOfFrames, int totalWidth)
{
	Spritesheet::numOfAnimations = numOfAnimations;
	Spritesheet::numOfFrames = numOfFrames;
	Spritesheet::sizes = sizes;

	currentPosition.x = 0;
	currentPosition.y = 0;
	currentSize.x = sizes[0].x;
	currentSize.y = sizes[0].y;
	currentAnimation = 0;

	Parse(sizes, numOfAnimations, numOfFrames, totalWidth);
}

void Spritesheet::Update(int animationState, int currentFrame)
{
	currentAnimation = animationState;

	//Starting frame of the animation
	int initialFrame = 0;
	for (int i = 0; i < currentAnimation; i++)
	{
		initialFrame += numOfFrames[i];
	}

	currentPosition = positions[initialFrame + currentFrame];
	currentSize = sizes[currentAnimation];
}

void Spritesheet::Parse(vector<XMFLOAT2> sizes, int numOfAnimations, vector<int> numOfFrames, int totalWidth)
{
	// variables for keeping track of row and column position.
	XMFLOAT2 currentPos;
	currentPos.x = 0;
	currentPos.y = 0;

	//int rowWidth = 0;
	//int columnHeight = 0;

	// potentially correct, still needs testing
	// k is whichever animation you are on
	// i simply iterates through the frames in that animation
	for (int k = 0; k < numOfAnimations; k++)
	{
		for (int i = 0; i < numOfFrames[k]; i++)
		{
			if (k == 0 && i == 0)
			{
				positions.push_back(currentPos);
			}
			else
			{
				currentPos.x += sizes[k].x;
				if (currentPos.x >= totalWidth)
				{
					currentPos.y += sizes[k].y;
					currentPos.x = 0;
				}
				positions.push_back(currentPos);
			}
		}
	}
}