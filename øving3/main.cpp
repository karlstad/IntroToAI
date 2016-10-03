#include <iostream>
#include <fstream>

#include "readboard.h"

using namespace std;

int main(){
	string small_board_files[] = {"boards/board-1-1.txt", "boards/board-1-2.txt", "boards/board-1-3.txt", "boards/board-1-4.txt"};
	string large_board_files[] = {"boards/board-2-1.txt", "boards/board-2-2.txt", "boards/board-2-3.txt", "boards/board-2-4.txt"};

	Node* backtrackingNode;

	for(int i = 0; i < 4; i++){
		Node** board = new Node*[BOARD_WIDTH];
		for(int i = 0; i < BOARD_WIDTH; i++){
			board[i] = new Node[BOARD_HEIGTH];
		}
		readBoard(board, large_board_files[i]);
		
		backtrackingNode = findPath_BFS(board)->parent;
		cout << "Cost to destination: " << backtrackingNode->g << endl;
		
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
		cout << endl << endl;

		for(int i = 0; i < BOARD_WIDTH; i++){
			delete[] board[i];
		}
		delete[] board;
	}


	return 0;
}