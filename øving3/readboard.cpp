#include <fstream>
#include <string>
#include <iostream>

#include "readboard.h"

using namespace std;

void readBoard(Node** board, string filename){
	ifstream in(filename);
	if(!in){
		cout << "Could not open file " << filename << endl;
	}
	string line;
	int j = 0;
	while(getline(in, line)){
		for(int i = 0; i < line.length(); i++){
			board[i][j].value = line[i];
			board[i][j].x = i;
			board[i][j].y = j;
			board[i][j].cost = costMap(line[i]);
			//cout << line[i];
		}
		j++;
		//cout << endl;
	}

	in.close();
}

int costMap(char value){
	switch(value){
		case 'w':
			return 100;
		case 'm':
			return 50;
		case 'f':
			return 10;
		case 'g':
			return 5;
		case 'r':
			return 1;
		case '.':
			return 1;
		case '#':
			return 10000;
		default:
			return 0;
	}
}