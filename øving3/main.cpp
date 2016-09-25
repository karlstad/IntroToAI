#include <iostream>

#include "readboard.h"

int main(){
	char** board = new char*[20];
	for(int i = 0; i < 20; i++){
		board[i] = new char[7];
	}

	readBoard(board, "boards/board-1-1.txt");


	return 0;
}