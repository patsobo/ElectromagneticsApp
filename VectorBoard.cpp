#include "pch.h"

#include "VectorBoard.h"

using namespace DirectX;
using namespace std;
	
// TODO: GET RID OF THE FUCKING MAGIC NUMBERS
VectorBoard::VectorBoard(ID3D11ShaderResourceView* arrowTexture, XMFLOAT2 boardSize, Windows::Foundation::Rect* movementBounds) {
	this->movementBounds = movementBounds;

	XMFLOAT2 unitLength = XMFLOAT2(movementBounds->Width / boardSize.x, movementBounds->Height / boardSize.y);
	//XMFLOAT2 unitLength = XMFLOAT2(60, 60);
	XMFLOAT2 origin = XMFLOAT2(0, 457 / 2);	// Origin is point is found before scaling of image.
	for (int i = 0; i < boardSize.x - 1; i++) {	// -1 because it needs extra space
		vector<VectorCell*> row;
		for (int j = 0; j < boardSize.y - 1; j++ ) {
			XMFLOAT2 position = XMFLOAT2(unitLength.x * i + 60, unitLength.y * j + 60);	// Includes offset, for now
			row.push_back(new VectorCell(new Sprite(arrowTexture, XMFLOAT2(600, 457), position, movementBounds, .1, 0, origin), position));
		}
		board.push_back(row);
		row.clear();
	}		
}
	
void VectorBoard::Update(float timeTotal, float timeDelta, vector<ElectricObject> electricObjects) {
	//for(int i=0; i<board.size(); i++) {
	//	for(int j =0; j<board[i].size();j++) {
	//		//board[i][j]->setFieldLine(calculateSum(i, j, electricObjects));
	//		board[i][j]->Update(timeTotal, timeDelta);
	//	}
	//}
	calculateSum(electricObjects);
}
	
void VectorBoard::Draw(SpriteBatch* spriteBatch) {
	for(int i=0; i < board.size(); i++) {
		for(int j =0; j < board[i].size();j++) {
			board[i][j]->Draw(spriteBatch); 
		}
	}
}
	
void VectorBoard::calculateSum(vector<ElectricObject> electricObjects){
	XMFLOAT2 field = XMFLOAT2(0, 0);
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			for (ElectricObject thing : electricObjects) {
				XMFLOAT2 singleField = thing.calculateField(board[i][j]->getPosition());
				field.x += singleField.x;
				field.y += singleField.y;
			}
			board[i][j]->setFieldLine(field);
		}
	}
}


// TODO: TEST METHOD ONLY.  DELETE WHEN FINISHED
void VectorBoard::addField(XMFLOAT2 field) {
	for (int i = 0; i<board.size(); i++) {
		for (int j = 0; j<board[i].size(); j++) {
			if (abs(board[i][j]->getFieldLine().x) > MAX_STRENGTH)
				board[i][j]->setFieldLine(XMFLOAT2(MAX_STRENGTH * board[i][j]->getFieldLine().x / abs(board[i][j]->getFieldLine().x), board[i][j]->getFieldLine().y));
			if (abs(board[i][j]->getFieldLine().y) > MAX_STRENGTH)
				board[i][j]->setFieldLine(XMFLOAT2(board[i][j]->getFieldLine().x, MAX_STRENGTH * board[i][j]->getFieldLine().y / abs(board[i][j]->getFieldLine().y)));
			board[i][j]->setFieldLine(XMFLOAT2(board[i][j]->getFieldLine().x + field.x, board[i][j]->getFieldLine().y + field.y));
		}
	}
}