#include <iostream>

#include "readboard.h"

using namespace std;

int main(){
	Node** board = new Node*[20];
	for(int i = 0; i < 20; i++){
		board[i] = new Node[7];
	}

	Node* backtrackingNode;

	readBoard(board, "boards/board-1-1.txt");
	
	backtrackingNode = findPath(board);
	
	//Solution found, backtracking the steps
	while(backtrackingNode->parent != NULL){
		backtrackingNode = backtrackingNode->parent;
		backtrackingNode->value = 'o';
	}
	backtrackingNode->value = 'A';
	for(int y = 0; y < 7; y++){
		for(int x = 0; x < 20; x++){		
			cout << board[x][y].value;
		}
		cout << endl;
	}


	return 0;
}