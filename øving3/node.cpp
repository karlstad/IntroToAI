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

	for(int y = 0; y < BOARD_HEIGTH; y++){
		for(int x = 0; x < BOARD_WIDTH; x++){
			if(board[x][y].value == 'A'){
				currentNode = &board[x][y];
				//cout << board[x][y].x << endl;
			} else if(board[x][y].value == 'B'){
				destination = &board[x][y];
			}

		}
	}

	currentNode->g = currentNode->cost;
	currentNode->h = abs(destination->x - currentNode->x) + abs(destination->y - currentNode->y);
	currentNode->f = currentNode->g + currentNode->h;
	open.push_back(currentNode);
	currentNode->state = OPEN;

	while(currentNode->f != 0){
		/*cout << "Open: " << endl;
		for(auto it = open.begin(); it != open.end(); ++it){
			cout << "x: " << (*it)->x << " y: " << (*it)->y << endl;
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
		for(int y = 0; y < BOARD_HEIGTH; y++){
			for(int x = 0; x < BOARD_WIDTH; x++){
				cout << board[x][y].cost << " ";
			}
			cout << endl;
		}
*/
		
		closed.push_back(currentNode);
		currentNode->state = CLOSED;
		//cout << "Current pos: x " << currentNode->x << " y " << currentNode->y << endl;


		for(int dir = 0; dir < 4; dir++){
			if(currentNode->x + dx[dir] >= 0 && currentNode->x + dx[dir] < BOARD_WIDTH && currentNode->y + dy[dir] >= 0 && currentNode->y + dy[dir] < BOARD_HEIGTH){
				//board[currentNode->x + dx[dir]][currentNode->y + dy[dir]].value = 'o';
				child = &board[currentNode->x + dx[dir]][currentNode->y + dy[dir]];
				if(child->state == UNKNOWN){
					child->parent = currentNode;
					child->g = currentNode->g + child->cost; //Update to handle variable arc cost
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
				} else if((currentNode->g + child->cost) <= child->g){ //Update to handle variable arc cost
					child->parent = currentNode;
					child->g = currentNode->g + child->cost; //Update to handle variable arc cost
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