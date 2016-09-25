#include <fstream>
#include <string>
#include <iostream>

#include "readboard.h"

using namespace std;

void readBoard(char** board, std::string filename){
	ifstream in(filename);
	if(!in){
		cout << "Could not open file " << filename << endl;
	}
	string line;
	int j = 0;
	while(getline(in, line)){
		for(int i = 0; i < line.length(); i++){
			board[j][i] = line[i];
			cout << line[i];
		}
		j++;
		cout << endl;
	}

	in.close();
}