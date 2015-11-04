#include "pch.h"

#include "VectorBoard.h"

using namespace DirectX;
using namespace std;
	
VectorBoard::VectorBoard(Sprite* arrow, XMFLOAT2 boardSize, Windows::Foundation::Rect* movementBounds) {
	this->movementBounds = movementBounds;

	XMFLOAT2 unitLength = XMFLOAT2(movementBounds->Width / boardSize.x, movementBounds->Height / boardSize.y);
	for (int i = 0; i < boardSize.x; i++) {
		vector<VectorCell*> row;
		for (int j = 0; j < boardSize.y; j++ ) {
			XMFLOAT2 position = XMFLOAT2(unitLength.x * i, unitLength.y * j);
			row.push_back(new VectorCell(arrow, position));
		}
		board.push_back(row);
		row.clear();
	}		
}
	
void VectorBoard::Update(float timeTotal, float timeDelta, vector<ElectricObject> electricObjects) {
	for(int i=0; i<board.size(); i++) {
		for(int j =0; j<board[i].size();j++) {
			VectorCell* cell = board[i][j];
			cell->setFieldLine(calculateSum(i, j, electricObjects));
			cell->Update(timeTotal, timeDelta);
		}
	}
		
}
	
void VectorBoard::Draw(SpriteBatch* spriteBatch) {
	for(int i=0; i<board.size(); i++) {
		for(int j =0; j<board[i].size();j++) {
			VectorCell* cell = board[i][j];
			cell->Draw(spriteBatch);
		}
	}
}
	
XMFLOAT2 VectorBoard::calculateSum(int i, int j, vector<ElectricObject> electricObjects){
	XMFLOAT2 sum = XMFLOAT2(0, 0);
	for (ElectricObject thing : electricObjects) {
		//sum.x += thing.getGrid()[i][j].getVector().x;
		//sum.y += thing.getGrid()[i][j].getVector().y;
		continue;
	}	
		
	return sum;
}