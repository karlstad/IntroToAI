#include <iostream>

#include "readboard.h"

using namespace std;

int main(){
	Node** board = new Node*[BOARD_WIDTH];
	for(int i = 0; i < BOARD_WIDTH; i++){
		board[i] = new Node[BOARD_HEIGTH];
	}

	Node* backtrackingNode;

	readBoard(board, "boards/board-1-4.txt");
	
	backtrackingNode = findPath(board)->parent;
	
	//Solution found, backtracking the steps
	while(backtrackingNode->parent != NULL){
		backtrackingNode->value = 'o';
		backtrackingNode = backtrackingNode->parent;
	}
	for(int y = 0; y < BOARD_HEIGTH; y++){
		for(int x = 0; x < BOARD_WIDTH; x++){		
			cout << board[x][y].value;
		}
		cout << endl;
	}


	return 0;
}