#include <vector>
#include <stdlib.h>
#include <iostream>

#include "node.h"

using namespace std;

Node* findPath(Node** board){
	vector<Node*> open;
	vector<Node*> closed;
	vector<Node*> successors;
	Node* currentNode;
	Node* destination;


	for(int y = 0; y < 7; y++){
		for(int x = 0; x < 20; x++){
			if(board[x][y].value == 'A'){
				currentNode = &board[x][y];
				//cout << &board[x][y] << endl;
			} else if(board[x][y].value == 'B'){
				destination = &board[x][y];
			}

		}
	}
	currentNode->g = 0;
	currentNode->h = abs(destination->x - currentNode->x) + abs(destination->y - currentNode->y);
	currentNode->f = currentNode->g + currentNode->h;
	open.push_back(currentNode);
	currentNode->state = OPEN;

	while(currentNode->f != 0){
		/*cout << "Open: " << endl;
		for(int i = 0; i < open.size(); i++){
			cout << open[i]->x << " ";
		}
		cout << endl;*/
		currentNode = open[0];
		open.erase(open.begin());
		closed.push_back(currentNode);
		//cout << "Current pos: x " << currentNode->x << " y " << currentNode->y << endl;


		//Check for solution
		if(!currentNode->f){
			return currentNode;
		}

		cout << &board << endl;
		generate_successors(board, &successors, currentNode);
		cout << 4 << endl;
		currentNode->kids = successors;
		for(int i = 0; i < successors.size(); i++){
			if(successors[i]->state == UNKNOWN){
				attach_and_eval(successors[i], currentNode, destination);
				insert_sorted(&open, successors[i]);
			} else if((currentNode->g + 1) < successors[i]->g){ //Update to handle variable arc cost
				attach_and_eval(successors[i], currentNode, destination);
				if(successors[i]->state == CLOSED){
					propagate_path_improvements(successors[i]);
				}
			}
		}
	}
}

void generate_successors(Node** board, vector<Node*>* successors, Node* currentNode){
	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};

	cout << &board << endl;
	for(int dir = 0; dir < 4; dir++){
		if(board[currentNode->x + dx[dir]][currentNode->y + dy[dir]].value != '#'){
			successors->push_back(&board[currentNode->x + dx[dir]][currentNode->y + dy[dir]]);
		}
	}
}

void attach_and_eval(Node* kid, Node* currentNode, Node* destination){
	kid->parent = currentNode;
	kid->g = currentNode->g + 1; //Update to handle variable arc cost
	kid->h = abs(destination->x - kid->x) + abs(destination->y - kid->y);
	kid->f = kid->h + kid->g;
}

void insert_sorted(vector<Node*>* vec, Node* node){
	vector<Node*>::iterator it;
	for(it = vec->begin(); it != vec->end(); ++it){
		cout << "halla" << endl;
		if((*it)->f < node->f){
			vec->insert(it, node);
			return;
		}
	}
}

void propagate_path_improvements(Node* node){
	for(int i = 0; i < node->kids.size(); i++){
		if(node->g + 1 < node->kids[i]->g){
			node->kids[i]->parent = node;
			node->kids[i]->g = node->g + 1;
			node->kids[i]->f = node->kids[i]->g + node->kids[i]->h;
			propagate_path_improvements(node->kids[i]);
		}
	}
}