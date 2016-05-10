/*
Sprite.h

Sprite Parent Class

A 2D sprite that accepts a texture and draws and animates the sprite based on set Velocities, Speed,
position, etc.  It is very flexible, as scale, FPS, as well as Velocity, Speed, and position, can all
be changed.

The two main methods of the class are Draw and Update - they are called in the game loop to draw the actually
sprite to the screen, and to calculate the position and animation frame the sprite should currently be on
(respectively).

authors: Patrick Sobolewski
*/

#pragma once

#include "SpriteBatch.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>
#include "Spritesheet.h"

using namespace DirectX;
using namespace std;

const int POS_ADJUST = 1;

class Sprite
{

// constructors
public:
	Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, float scale = 1,
		float Speed = 0, XMFLOAT2 origin = XMFLOAT2(0, 0));
	Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMVECTORF32* color,
		float scale = 1, float Speed = 0, XMFLOAT2 origin = XMFLOAT2(0, 0));
	Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, int rows, int columns,
		double framesPerSecond, int dividers[]);
	Sprite(Spritesheet* spritesheet, ID3D11ShaderResourceView *m_Texture, XMFLOAT2 position,
		Windows::Foundation::Rect* movementBounds, float Speed, double framesPerSecond, float scale);


// Major loop methods
public:
	// Draws the sprites texture to the screen
	virtual void Draw(SpriteBatch* spriteBatch);

	// Updates the position and animation frame
	virtual void Update(float timeTotal, float timeDelta);


// public utilities
public:
	// Checks if this sprite is touching that sprite
	bool CollidesWith(Sprite* that);

	// Resets the position and velocity of the sprite, called when new game happens
	void reset();

	// Moves sprite slightly backwards, it's called when two sprites are colliding and 
	// this sprite needs to move back to no longer be colliding
	void adjustPosition();


// getters and setters
public:
	void setAnimation(int newAnim);
	int getAnimation();
	void setFrame(int newFrame);
	int getNumFrames();
	float getWidth();
	float getHeight();
	XMFLOAT2 getVelocity();
	void setVelocity(XMFLOAT2 newVelocity);
	Windows::Foundation::Rect* getBoundingBox();
	void setPosition(XMFLOAT2 newPosition);
	void setOpacity(float newOpacity);
	void setRotation(float newRotation);
	XMFLOAT2 getPosition();


private:
	// The spritesheet, which properly parses the texture to spit out the correct frame
	Spritesheet spritesheet;
	
	// Current frame that is being drawn to the screen
	int currentFrame;

	// Controls which part of the sprite sheet to animate (therefore, created sprites MUST modify this value)
	int animationState; 

	// The speed of the animation (as frames per second, obviously)
	int framesPerSecond;

	// Keeps track of how much time has passed since frame has changed; so, when this value exceeds
	// the value returned by SecondsBetweenFrames(), it's time to change frames
	double timeSinceLastFrame;

	// How much you should blow up each frame of the texture image
	float scale;

	// How much to rotate the frame of the texture image
	float rotation;

	// Defines the origin of the actual texture (top-left corner, middle, etc.)
	XMFLOAT2 origin;

	// The boundary on which the sprite can move
	Windows::Foundation::Rect* movementBounds;

	// The box defining the space that the sprite is physically taking up
	Windows::Foundation::Rect* BoundingBox;


// private utilities
private:

	void NormalizeVelocity();
	Windows::Foundation::Rect* Sprite::CreateBoundingBoxFromPosition(XMFLOAT2 position);

	// Calculates the seconds that should be between each page based on the framesPerSecond
	double SecondsBetweenFrames();

// Variables that children can change
protected:
	// The direction the sprite should be moving
	XMFLOAT2 Velocity;

	// The scale of the Velocity
	float Speed;

	// The color of the sprite, which should generally just be White if you want the sprite to look normal
	XMVECTORF32 color;
	XMFLOAT2 initialPosition;	// For resetting
	XMFLOAT2 position;

	// Is true if the animation has looped through once
	bool animationPlayedOnce;

	// The texture for the sprite
	ID3D11ShaderResourceView* m_Texture;

	// An enum indicating if the sprite should have any effects (flip horizontal or flip vertical)
	SpriteEffects spriteEffects;


// Utilities that children can alter depending on their needs
protected:
	// Returns true if the newPosition will cause the sprite to hit its movementBounds
	bool Blocked(XMFLOAT2 newPosition);

	// Updates the animation (is called within the Update method)
	void UpdateAnimation(float timeTotal, float timeDelta);

	// Updates the position (is called within the Update method)
	void UpdatePosition(float timeTotal, float timeDelta);
};
