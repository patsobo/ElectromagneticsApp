#include "pch.h"
#include "ElectricObjectManager.h"

ElectricObjectManager::ElectricObjectManager(Sprite* box, ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize)
{
	this->creationBox = box;
	this->texture = m_Texture;
	this->size = size;
	Windows::Foundation::Rect posBox = *box->getBoundingBox();
	this->position = XMFLOAT2(posBox.X + posBox.Width / 2, posBox.Y + posBox.Height / 2);	// center of the box
	this->movementBounds = movementBounds;
	this->boardSize = boardSize;
}

void ElectricObjectManager::Update(float timeTotal, float timeDelta) {
	creationBox->Update(timeTotal, timeDelta);
	for (ElectricObject* thing : electricObjects) {
		thing->Update(timeTotal, timeDelta);
	}
}

void ElectricObjectManager::Draw(SpriteBatch* spriteBatch) {
	creationBox->Draw(spriteBatch);
	for (ElectricObject* thing : electricObjects)
		thing->Draw(spriteBatch);
}

// Checks if any objects should be deleted
void ElectricObjectManager::checkForDeleteObject() {
	for (int i = 0; i < electricObjects.size(); i++) {
		if (creationBox->CollidesWith(electricObjects[i])) {
			delete electricObjects[i];
			electricObjects.erase(electricObjects.begin() + i);
			return;
		}
		//if (thing == test) {
		//	electricObjects.erase(electricObjects.begin(), electricObjects.end() + i);
		//	delete test;
		//	return;
		//}
	}
}

void ElectricObjectManager::createObject() {
	electricObjects.push_back(new ElectricObject(texture, size, position, movementBounds, boardSize));
	electricObjects[electricObjects.size() - 1]->isMoving = true;
}

Sprite* ElectricObjectManager::getCreationBox() { return creationBox; }
vector<ElectricObject*> ElectricObjectManager::getElectricObjects() { return electricObjects; }