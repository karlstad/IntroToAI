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
	cout << &board << endl;
	backtrackingNode = findPath(board);
	
	//Solution found, backtracking the steps
	while(backtrackingNode->parent != NULL){
		backtrackingNode->value = 'o';
		backtrackingNode = backtrackingNode->parent;
	}

	for(int i = 0; i < 7; i++){
		for(int j = 0; j < 20; j++){		
			cout << board[i][j].value;
		}
		cout << endl;
	}


	return 0;
}