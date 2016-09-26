#include <list>
#include <stdlib.h>
#include <iostream>

#include "node.h"

using namespace std;

Node* findPath(Node** board){
	list<Node*> open;
	list<Node*> closed;
	//list<Node*> successors;
	Node* child;
	
	Node* currentNode;
	Node* destination;

	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};

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

	currentNode->h = abs(destination->x - currentNode->x) + abs(destination->y - currentNode->y);
	currentNode->f = currentNode->g + currentNode->h;
	open.push_back(currentNode);
	currentNode->state = OPEN;

	while(currentNode->f != 0){
		/*cout << "Open: " << endl;
		for(auto it = open.begin(); it != open.end(); ++it){
			cout << (*it)->x << " ";
		}
		cout << endl;*/
		if(open.empty()){
			cout << "Algorithm failed to find path" << endl;
			return NULL;
		}


		currentNode = *(open.begin());
		open.remove(currentNode);

		//Check for solution
		if((currentNode->f == 0) || (currentNode == destination)){
			return currentNode;
		}
/*
		for(int y = 0; y < 7; y++){
			for(int x = 0; x < 20; x++){
				cout << board[x][y].state;
			}
			cout << endl;
		}
*/
		
		closed.push_back(currentNode);
		currentNode->state = CLOSED;
		//cout << "Current pos: x " << currentNode->x << " y " << currentNode->y << endl;


		for(int dir = 0; dir < 4; dir++){
			if(board[currentNode->x + dx[dir]][currentNode->y + dy[dir]].value != '#'){
				child = &board[currentNode->x + dx[dir]][currentNode->y + dy[dir]];
				if(child->state == UNKNOWN){
					child->parent = currentNode;
					child->g = currentNode->g + 1; //Update to handle variable arc cost
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					
					if(open.empty()){
						open.push_back(child);
					} else{
						for(auto it = open.begin(); it != open.end(); ++it){
							if(child->f < (*it)->f ){
								open.insert(it, child);
								break;
							}
						}
						open.push_back(child);
					}
					child->state = OPEN;
				} else if((currentNode->g + 1) < child->g){ //Update to handle variable arc cost
					child->parent = currentNode;
					child->g = currentNode->g + 1; //Update to handle variable arc cost
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					/*if(successors[i]->state == CLOSED){
						propagate_path_improvements(successors[i]);
					}*/
				}
			}
		}
	}
}
/*
void generate_successors(Node** board, vector<Node*>* successors, Node* currentNode){
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
}*/