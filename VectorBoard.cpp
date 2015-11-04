#include "pch.h"

#include "VectorBoard.h"

using namespace DirectX;
using namespace std;
	
// TODO: GET RID OF THE FUCKING MAGIC NUMBERS
VectorBoard::VectorBoard(ID3D11ShaderResourceView* arrowTexture, XMFLOAT2 boardSize, Windows::Foundation::Rect* movementBounds) {
	this->movementBounds = movementBounds;

	//XMFLOAT2 unitLength = XMFLOAT2(movementBounds->Width / boardSize.x, movementBounds->Height / boardSize.y);
	XMFLOAT2 unitLength = XMFLOAT2(60, 60);
	XMFLOAT2 origin = XMFLOAT2(0, 457 * .1 / 2);
	for (int i = 0; i < boardSize.x; i++) {
		vector<VectorCell*> row;
		for (int j = 0; j < boardSize.y; j++ ) {
			XMFLOAT2 position = XMFLOAT2(unitLength.x * i, unitLength.y * j + 457*.1 / 2);	// Includes offset, for now
			row.push_back(new VectorCell(new Sprite(arrowTexture, XMFLOAT2(600, 457), position, movementBounds, .1, 0, origin), position));
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