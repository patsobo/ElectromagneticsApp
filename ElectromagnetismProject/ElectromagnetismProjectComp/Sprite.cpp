#include "pch.h"
#include "Sprite.h"

using namespace DirectX;
using namespace std;

Sprite::Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, float scale, float Speed, XMFLOAT2 origin) :
m_Texture(m_Texture), size(size), position(position), movementBounds(movementBounds), rows(1), columns(1), framesPerSecond(1), Velocity(XMFLOAT2(0, 0))
{
	this->position = position;
	this->movementBounds = movementBounds;
	this->m_Texture = m_Texture;
	this->scale = scale;
	this->Speed = Speed;
	this->initialPosition = position;
	this->spritesheet = Spritesheet(size);
	this->color = Colors::White;
	this->origin = origin;

	animationState = 0;
	currentFrame = 0;
	totalFrames = rows*columns;
	BoundingBox = CreateBoundingBoxFromPosition(Sprite::position);
	shouldChangeAnimation = false;
	timeSinceLastFrame = 0;
	rotation = 0.0f;
	spriteEffects = SpriteEffects_None;
}

Sprite::Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, XMVECTORF32* color, float scale, float Speed, XMFLOAT2 origin) :
m_Texture(m_Texture), size(size), position(position), movementBounds(movementBounds), rows(1), columns(1), framesPerSecond(1), Velocity(XMFLOAT2(0, 0))
{
	this->position = position;
	this->movementBounds = movementBounds;
	this->m_Texture = m_Texture;
	this->scale = scale;
	this->Speed = Speed;
	this->initialPosition = position;
	this->spritesheet = Spritesheet(size);
	this->color = *color;
	this->origin = origin;

	animationState = 0;
	currentFrame = 0;
	totalFrames = rows*columns;
	BoundingBox = CreateBoundingBoxFromPosition(Sprite::position);
	shouldChangeAnimation = false;
	timeSinceLastFrame = 0;
	rotation = 0.0f;
	spriteEffects = SpriteEffects_None;
}

//Sprite::Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, float scale) :
//m_Texture(m_Texture), size(size), position(position), movementBounds(movementBounds), rows(1), columns(1), framesPerSecond(1)
//{
//	this->position = position;
//	this->movementBounds = movementBounds;
//	this->m_Texture = m_Texture;
//	this->size = size;
//	this->scale = scale;
//
//	for (int i = 0; i < 5; i++)
//	{
//		this->dividers[i] = 0;
//	}
//
//	animationState = 0;
//	currentFrame = 0;
//	totalFrames = rows*columns;
//	BoundingBox = CreateBoundingBoxFromPosition(Sprite::position);
//	shouldChangeAnimation = false;
//	timeSinceLastFrame = 0;
//}

Sprite::Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, int rows, int columns,
	double framesPerSecond, int dividers[])
{
	this->position = position;
	this->initialPosition = position;
	this->movementBounds = movementBounds;
	this->rows = rows;
	this->columns = columns;
	this->framesPerSecond = framesPerSecond;
	this->spritesheet = Spritesheet(size);
	scale = 1;
	this->color = Colors::White;

	this->m_Texture = m_Texture;
	this->size = size;

	animationState = 0;
	currentFrame = 0;
	totalFrames = rows*columns;
	BoundingBox = CreateBoundingBoxFromPosition(this->position);
	shouldChangeAnimation = false;
	timeSinceLastFrame = 0;
	rotation = 0.0f;
	spriteEffects = SpriteEffects_None;
	origin = XMFLOAT2(0, 0);
}

Sprite::Sprite(Spritesheet* spritesheet, ID3D11ShaderResourceView *m_Texture, XMFLOAT2 position,
	Windows::Foundation::Rect* movementBounds, float Speed, double framesPerSecond, float scale)
{
	this->position = position;
	this->initialPosition = position;
	this->movementBounds = movementBounds;
	this->framesPerSecond = framesPerSecond;
	this->spritesheet = *spritesheet;
	this->Speed = Speed;
	this->m_Texture = m_Texture;
	this->color = Colors::White;

	currentFrame = 0;
	this->scale = scale;
	rotation = 0.0f;
	BoundingBox = CreateBoundingBoxFromPosition(this->position);
	timeSinceLastFrame = 0;
	spriteEffects = SpriteEffects_None;
	origin = XMFLOAT2(0, 0);
}

void Sprite::Draw(SpriteBatch* spriteBatch)
{
	//double imageWidth = size.x / columns;
	//double imageHeight = size.y / rows;

	//int currentRow = currentFrame / columns;
	//int currentColumn = currentFrame%columns;

	//RECT* sourceRectangle = new RECT;
	//sourceRectangle->left = imageWidth*currentColumn;
	//sourceRectangle->top = imageHeight*currentRow;
	//sourceRectangle->right = imageWidth*currentColumn + imageWidth;
	//sourceRectangle->bottom = imageHeight*currentRow + imageHeight;

	double imageWidth = spritesheet.currentSize.x;
	double imageHeight = spritesheet.currentSize.y;

	RECT* sourceRectangle = new RECT;
	sourceRectangle->left = spritesheet.currentPosition.x;
	sourceRectangle->top = spritesheet.currentPosition.y;
	sourceRectangle->right = spritesheet.currentPosition.x + spritesheet.currentSize.x;
	sourceRectangle->bottom = spritesheet.currentPosition.y + spritesheet.currentSize.y;

	spriteBatch->Draw(m_Texture, position,
		sourceRectangle, color, rotation, origin,
		XMFLOAT2(getWidth() / imageWidth, getHeight() / imageHeight),
		spriteEffects, 0.0f);
}

void Sprite::Update(float timeTotal, float timeDelta)
{
	UpdateAnimation(timeTotal, timeDelta);
	UpdatePosition(timeTotal, timeDelta);
}

void Sprite::UpdateAnimation(float timeTotal, float timeDelta)
{
	timeSinceLastFrame += timeDelta;

	//if (timeSinceLastFrame > SecondsBetweenFrames() && !shouldChangeAnimation)	//continue animating as normal
	//{
	//	currentFrame++;
	//	timeSinceLastFrame = 0;
	//}

	////else if (shouldChangeAnimation && inSecondAnimation)	//if should change out of second animation, go to first animation
	////{
	////	currentFrame = 0;
	////	timeSinceLastFrame = 0;
	////	shouldChangeAnimation = false;
	////}

	//else if (shouldChangeAnimation)	//go to specified animation
	//{
	//	currentFrame = dividers[animationState];
	//	timeSinceLastFrame = 0;
	//	shouldChangeAnimation = false;
	//	animationPlayedOnce = false;
	//}

	////looping conditional statements
	//if (currentFrame == dividers[animationState + 1] - 1 && dividers[animationState + 1] != 0)	//if you reach the end of your animation, loop that animation again
	//{
	//	currentFrame = dividers[animationState];
	//	animationPlayedOnce = true;
	//}

	//else if (currentFrame == totalFrames)	//if at the end of sprite sheet, loop animation again
	//{
	//	currentFrame = dividers[animationState];
	//	timeSinceLastFrame = 0;
	//	animationPlayedOnce = true;
	//}

	// Continue animating as normal
	if (timeSinceLastFrame > SecondsBetweenFrames())
	{
		currentFrame++;
		timeSinceLastFrame = 0;
	}

	// If you reach the end of your animation, loop that animation again
	if (currentFrame >= spritesheet.numOfFrames[spritesheet.currentAnimation])
	{
		currentFrame = 0;
		animationPlayedOnce = true;
	}
	//else currentFrame = 0;

	// Update the source rectangle
	spritesheet.Update(spritesheet.currentAnimation, currentFrame);
}

void Sprite::UpdatePosition(float timeTotal, float timeDelta)
{
	XMFLOAT2 newPosition;
	newPosition.x = position.x + ((Velocity.x * timeDelta) * Speed);
	newPosition.y = position.y + ((Velocity.y * timeDelta) * Speed);

	if (Blocked(newPosition))
	{
		BoundingBox = CreateBoundingBoxFromPosition(position);
		return;
	}
	BoundingBox = CreateBoundingBoxFromPosition(newPosition);
	position = newPosition;
}

void Sprite::reset()
{
	position = initialPosition;
	Velocity = XMFLOAT2(0, 0);
}

double Sprite::SecondsBetweenFrames() {	return 1.0 / framesPerSecond; }

bool Sprite::Blocked(XMFLOAT2 newPosition)
{
	BoundingBox = CreateBoundingBoxFromPosition(newPosition);

	Windows::Foundation::Point topLeft(BoundingBox->X, BoundingBox->Y);
	Windows::Foundation::Point topRight(BoundingBox->X + getWidth(), BoundingBox->Y);
	Windows::Foundation::Point bottomLeft(BoundingBox->X, BoundingBox->Y + getHeight());
	Windows::Foundation::Point bottomRight(BoundingBox->X + getWidth(), BoundingBox->Y + getHeight());

	return !((movementBounds->Contains(topLeft)) && (movementBounds->Contains(topRight)) && (movementBounds->Contains(bottomLeft)) &&
		(movementBounds->Contains(bottomRight)));
}

Windows::Foundation::Rect* Sprite::CreateBoundingBoxFromPosition(XMFLOAT2 position)
{
	// Need to account for origin
	return new Windows::Foundation::Rect(position.x - (origin.x*scale), position.y - (origin.y*scale), getWidth(), getHeight());
}

bool Sprite::CollidesWith(Sprite* that)
{
	if (this->BoundingBox->IntersectsWith(*that->getBoundingBox()))
		return true;
	return false;
}

void Sprite::NormalizeVelocity()
{
	if (Velocity.x == 0 && Velocity.y == 0)
		return;
	float magnitude = sqrt(pow(Velocity.x, 2) + pow(Velocity.y, 2));
	Velocity.x /= magnitude;
	Velocity.y /= magnitude;
}

void Sprite::adjustPosition()
{
	XMFLOAT2 adjustVelocity = XMFLOAT2(-1 * Velocity.x, -1 * Velocity.y);
	position.x += adjustVelocity.x * POS_ADJUST;
	position.y += adjustVelocity.y * POS_ADJUST;
	BoundingBox = CreateBoundingBoxFromPosition(position);
}

float Sprite::getWidth() { return spritesheet.currentSize.x * scale; }
float Sprite::getHeight() { return spritesheet.currentSize.y * scale; }
XMFLOAT2 Sprite::getVelocity() { return Velocity; }
void Sprite::setAnimation(int newAnim)
{
	spritesheet.currentAnimation = newAnim;
	currentFrame = 0;
	animationPlayedOnce = false;
}
int Sprite::getAnimation() { return spritesheet.currentAnimation; }
void Sprite::setFrame(int newFrame)
{
	if (newFrame < spritesheet.numOfFrames[spritesheet.currentAnimation] && newFrame >= 0)
		currentFrame = newFrame;
}
int Sprite::getNumFrames()
{
	return spritesheet.numOfFrames[spritesheet.currentAnimation];
}
void Sprite::setVelocity(XMFLOAT2 newVelocity)
{
	Velocity = newVelocity;
	NormalizeVelocity();
}
Windows::Foundation::Rect* Sprite::getBoundingBox() { return BoundingBox; }
void Sprite::setPosition(XMFLOAT2 newPosition) { 
	position = newPosition;
	BoundingBox = CreateBoundingBoxFromPosition(position);
}
void Sprite::setRotation(float newRotation) { rotation = newRotation; }
void Sprite::setOpacity(float newOpacity) {
	if (newOpacity >= 0 && newOpacity <= 1) {
		XMVECTORF32 newColor = { color[0], color[1], color[2], newOpacity };
		color = newColor;
		return;
	}
}
XMFLOAT2 Sprite::getPosition() { return position; }