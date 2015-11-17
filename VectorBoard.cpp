#include "pch.h"

#include "VectorBoard.h"

using namespace DirectX;
using namespace std;
	
// TODO: GET RID OF THE FUCKING MAGIC NUMBERS
VectorBoard::VectorBoard(ID3D11ShaderResourceView* arrowTexture, XMFLOAT2 boardSize, Windows::Foundation::Rect* movementBounds) {
	this->movementBounds = movementBounds;

	unitLength = XMFLOAT2(movementBounds->Width / boardSize.x, movementBounds->Height / boardSize.y);
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
	
void VectorBoard::Update(float timeTotal, float timeDelta, vector<ElectricObject*> electricObjects) {
	// Either have to run this double for loop twice for include the update call in the calculateSum method.  Hmm....
	for(int i=0; i<board.size(); i++) {
		for(int j =0; j<board[i].size();j++) {
			//board[i][j]->setFieldLine(calculateSum(i, j, electricObjects));
			board[i][j]->Update(timeTotal, timeDelta);
		}
	}
	calculateSum(electricObjects);
}
	
void VectorBoard::Draw(SpriteBatch* spriteBatch) {
	for(int i=0; i < board.size(); i++) {
		for(int j =0; j < board[i].size();j++) {
			board[i][j]->Draw(spriteBatch); 
		}
	}
}
	
void VectorBoard::calculateSum(vector<ElectricObject*> electricObjects){
	XMFLOAT2 field = XMFLOAT2(0, 0);
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			for (ElectricObject* thing : electricObjects) {
				XMFLOAT2 singleField = thing->calculateField(board[i][j]->getPosition());
				field.x += singleField.x;
				field.y += singleField.y;
			}
			board[i][j]->setFieldLine(field);
			field = XMFLOAT2(0, 0);
		}
	}
}

XMFLOAT2 VectorBoard::getClosestField(XMFLOAT2 position) {
	int x = position.x / unitLength.x - 1;
	if (position.x - x*unitLength.x > unitLength.x / 2 && x < board.size() - 1)
		x++;
	int y = position.y / unitLength.y - 1;

	if (position.y - y*unitLength.y > unitLength.y / 2 && y < board[0].size() - 1)
		y++;

	// Fix boundary errors
	y = y < 0 ? 0 : y;
	x = x < 0 ? 0 : x;
	x = x > board.size() - 1 ? board.size() - 1 : x;
	y = y > board[x].size() - 1 ? board[x].size() - 1 : y;

	return board[x][y]->getFieldLine();
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