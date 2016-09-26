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
			//cout << line[i];
		}
		j++;
		//cout << endl;
	}

	in.close();
}