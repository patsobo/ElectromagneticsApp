#include "pch.h"
#include "ElectricObjectManager.h"

ElectricObjectManager::ElectricObjectManager(map<Sprite*, ID3D11ShaderResourceView*> textures, XMFLOAT2 size, Windows::Foundation::Rect* movementBounds, XMFLOAT2 boardSize)
{
	this->textures = textures;
	this->size = size;
	this->movementBounds = movementBounds;
	this->boardSize = boardSize;
	this->position = XMFLOAT2(0, 0);
}

void ElectricObjectManager::Update(float timeTotal, float timeDelta) {
	for (auto pairs : textures) {
		Sprite* creationBox = pairs.first;
		creationBox->Update(timeTotal, timeDelta);
	}
	for (ElectricObject* thing : electricObjects) {
		thing->Update(timeTotal, timeDelta);
	}
	for (MagneticObject* thing : magneticObjects) {
		thing->Update(timeTotal, timeDelta);
	}
}

void ElectricObjectManager::Draw(SpriteBatch* spriteBatch) {
	for (auto pairs : textures) {
		auto creationBox = pairs.first;
		creationBox->Draw(spriteBatch);
	}
	for (ElectricObject* thing : electricObjects)
		thing->Draw(spriteBatch);
	for (MagneticObject* thing : magneticObjects)
		thing->Draw(spriteBatch);
}

// Checks if any objects should be deleted
void ElectricObjectManager::checkForDeleteObject() {
	for (int i = 0; i < electricObjects.size(); i++) {
		for (auto pairs : textures) {	// inefficient but it'll only loop once anyway so it's fine
			auto creationBox = pairs.first;
			if (creationBox->CollidesWith(electricObjects[i])) {
				delete electricObjects[i];
				electricObjects.erase(electricObjects.begin() + i);
				return;
			}
		}

		//if (thing == test) {
		//	electricObjects.erase(electricObjects.begin(), electricObjects.end() + i);
		//	delete test;
		//	return;
		//}
	}
	for (int i = 0; i < magneticObjects.size(); i++) {
		for (auto pairs : textures) {	// inefficient but it'll only loop once anyway so it's fine
			auto creationBox = pairs.first;
			if (creationBox->CollidesWith(magneticObjects[i])) {
				delete magneticObjects[i];
				magneticObjects.erase(magneticObjects.begin() + i);
				return;
			}
		}
	}
}

void ElectricObjectManager::checkForCreateObject(XMFLOAT2 point) {
	Windows::Foundation::Point pointPoint = Windows::Foundation::Point(point.x, point.y);
	for (auto pairs : textures) {
		auto creationBox = pairs.first;
		auto posBox = *creationBox->getBoundingBox();	// the bounding box
		if (creationBox->getBoundingBox()->Contains(pointPoint)) {

			if (point.x < movementBounds->Width - posBox.Width * 2) {	// if wire
				position = XMFLOAT2(movementBounds->Width / 2, posBox.Y);
				float current = .0001f;
				auto texture = textures[creationBox];
				magneticObjects.push_back(new MagneticObject(texture, XMFLOAT2(768, 20), position, movementBounds, boardSize, current, 1));
				magneticObjects[magneticObjects.size() - 1]->isMoving = true;
			}
			else {	// if charge object
				position = XMFLOAT2(posBox.X + posBox.Width / 2, posBox.Y + posBox.Height / 2);	// Set position correctly

				// I'm going to cry from this solution, but it's so late, so...
				// Yes, I'll determine charge from position.
				int charge = (position.x - (movementBounds->Width - posBox.Width)) / abs(position.x - (movementBounds->Width - posBox.Width));

				auto texture = textures[creationBox];
				electricObjects.push_back(new ElectricObject(texture, size, position, movementBounds, boardSize, charge, .1));
				electricObjects[electricObjects.size() - 1]->isMoving = true;
			}
			return;
		}
	}
}

void ElectricObjectManager::reset() {
	for (ElectricObject* object : electricObjects) {
		delete object;	// clear the actual data
	}
	electricObjects.clear();	// clear the list of objects

	for (MagneticObject* object : magneticObjects) {
		delete object;	// clear the actual data
	}
	magneticObjects.clear();	// clear the list of objects
}

vector<ElectricObject*> ElectricObjectManager::getElectricObjects() { return electricObjects; }
vector<MagneticObject*> ElectricObjectManager::getMagneticObjects() { return magneticObjects; }

// TEST METHOD
void ElectricObjectManager::addObject(ElectricObject* object) {
	electricObjects.push_back(object);
}