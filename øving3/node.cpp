#include <list>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "node.h"

using namespace std;

Node* findPath_AStar(Node** board){
	list<Node*> open;
	list<Node*> closed;

	Node* child;
	Node* currentNode;
	Node* destination;

	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};

	for(int y = 0; y < BOARD_HEIGTH; y++){
		for(int x = 0; x < BOARD_WIDTH; x++){
			if(board[x][y].value == 'A'){
				currentNode = &board[x][y];
			} else if(board[x][y].value == 'B'){
				destination = &board[x][y];
			}

		}
	}

	//Initialize first node
	currentNode->g = currentNode->cost;
	currentNode->h = abs(destination->x - currentNode->x) + abs(destination->y - currentNode->y);
	currentNode->f = currentNode->g + currentNode->h;
	open.push_back(currentNode);
	currentNode->state = OPEN;

	while(1){
		if(open.empty()){
			cout << "Algorithm failed to find path" << endl;
			return NULL;
		}

		currentNode = *(open.begin());
		open.remove(currentNode);

		//Check for solution
		if((currentNode->h == 0) || (currentNode == destination)){
			//Code to mark opened and closed lists
			// for(auto it = open.begin(); it != open.end(); ++it){
			// 	if((*it)->value != 'A')
			// 		(*it)->value = '*';
			// }
			// for(auto it = closed.begin(); it != closed.end(); ++it){
			// 	if((*it)->value != 'A')
			// 		(*it)->value = 'x';
			// }
			return currentNode;
		}
		
		closed.push_back(currentNode);
		currentNode->state = CLOSED;


		for(int dir = 0; dir < 4; dir++){
			if(currentNode->x + dx[dir] >= 0 && currentNode->x + dx[dir] < BOARD_WIDTH && currentNode->y + dy[dir] >= 0 && currentNode->y + dy[dir] < BOARD_HEIGTH){
				child = &board[currentNode->x + dx[dir]][currentNode->y + dy[dir]];
				currentNode->kids.push_back(child);
				//If the node is not discovered before, initialize it's f value and add it to open with ascending value
				if(child->state == UNKNOWN){
					child->parent = currentNode;
					child->g = currentNode->g + child->cost;
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
				//The node has been discovered before, add only of it is a shorter path
				} else if((currentNode->g + child->cost) <= child->g){ 
					child->parent = currentNode;
					child->g = currentNode->g + child->cost;
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					if(child->state == CLOSED){
						propagate_path_improvements(child);
					}
				}
			}
		}
	}
}


Node* findPath_BFS(Node** board){
	list<Node*> open;
	list<Node*> closed;

	Node* child;
	Node* currentNode;
	Node* destination;

	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};

	for(int y = 0; y < BOARD_HEIGTH; y++){
		for(int x = 0; x < BOARD_WIDTH; x++){
			if(board[x][y].value == 'A'){
				currentNode = &board[x][y];
			} else if(board[x][y].value == 'B'){
				destination = &board[x][y];
			}

		}
	}

	//Initialize first node
	currentNode->g = currentNode->cost;
	currentNode->h = abs(destination->x - currentNode->x) + abs(destination->y - currentNode->y);
	currentNode->f = currentNode->g + currentNode->h;
	open.push_back(currentNode);
	currentNode->state = OPEN;

	//Loop until every cell have been checked to find shortest path
	while(!open.empty()){
		currentNode = *(open.begin());
		open.remove(currentNode);

		closed.push_back(currentNode);
		currentNode->state = CLOSED;

		for(int dir = 0; dir < 4; dir++){
			//Check every direction and add if inside the board
			if(currentNode->x + dx[dir] >= 0 && currentNode->x + dx[dir] < BOARD_WIDTH && currentNode->y + dy[dir] >= 0 && currentNode->y + dy[dir] < BOARD_HEIGTH && board[currentNode->x + dx[dir]][currentNode->y + dy[dir]].value != '#'){
				child = &board[currentNode->x + dx[dir]][currentNode->y + dy[dir]];
				currentNode->kids.push_back(child);
				if(child->state == UNKNOWN){
					child->parent = currentNode;
					child->g = currentNode->g + child->cost;
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					
					//Add new child to the back of the open queue
					open.push_back(child);
					child->state = OPEN;
				} else if((currentNode->g + child->cost) < child->g){
					//Better path found, recursively update the kids if it is a closed node
					child->parent = currentNode;
					child->g = currentNode->g + child->cost;
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					if(child->state == CLOSED){
						propagate_path_improvements(child);
					}
				}
			}
		}
	}
	// for(auto it = open.begin(); it != open.end(); ++it){
	// 	if((*it)->value != 'A')
	// 		(*it)->value = '*';
	// }
	// for(auto it = closed.begin(); it != closed.end(); ++it){
	// 	if((*it)->value != 'A')
	// 		(*it)->value = 'x';
	// }
	return destination;
}

Node* findPath_Dijkstra(Node** board){
	list<Node*> open;
	list<Node*> closed;

	Node* child;
	Node* currentNode;
	Node* destination;

	int dx[] = {0, 1, 0, -1};
	int dy[] = {1, 0, -1, 0};

	for(int y = 0; y < BOARD_HEIGTH; y++){
		for(int x = 0; x < BOARD_WIDTH; x++){
			if(board[x][y].value == 'A'){
				currentNode = &board[x][y];
			} else if(board[x][y].value == 'B'){
				destination = &board[x][y];
			}

		}
	}

	//Initialize the first node
	currentNode->g = currentNode->cost;
	currentNode->h = abs(destination->x - currentNode->x) + abs(destination->y - currentNode->y);
	currentNode->f = currentNode->g + currentNode->h;
	open.push_back(currentNode);
	currentNode->state = OPEN;

	while(1){
		if(open.empty()){
			cout << "Algorithm failed to find path" << endl;
			return NULL;
		}

		currentNode = *(open.begin());
		open.remove(currentNode);

		//Check for solution
		if((currentNode->h == 0) || (currentNode == destination)){
			// for(auto it = open.begin(); it != open.end(); ++it){
			// 	if((*it)->value != 'A')
			// 		(*it)->value = '*';
			// }
			// for(auto it = closed.begin(); it != closed.end(); ++it){
			// 	if((*it)->value != 'A')
			// 		(*it)->value = 'x';
			// }
			return currentNode;
		}
		
		closed.push_back(currentNode);
		currentNode->state = CLOSED;

		for(int dir = 0; dir < 4; dir++){
			if(currentNode->x + dx[dir] >= 0 && currentNode->x + dx[dir] < BOARD_WIDTH && currentNode->y + dy[dir] >= 0 && currentNode->y + dy[dir] < BOARD_HEIGTH){
				child = &board[currentNode->x + dx[dir]][currentNode->y + dy[dir]];
				currentNode->kids.push_back(child);
				if(child->state == UNKNOWN){
					child->parent = currentNode;
					child->g = currentNode->g + child->cost;
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					
					//Add new child to open list with ascending g value
					if(open.empty()){
						open.push_back(child);
					} else{
						for(auto it = open.begin(); it != open.end(); ++it){
							if(child->g < (*it)->g ){
								open.insert(it, child);
								break;
							}
						}
						open.push_back(child);
					}
					child->state = OPEN;
				} else if((currentNode->g + child->cost) <= child->g){ 
					child->parent = currentNode;
					child->g = currentNode->g + child->cost;
					child->h = abs(destination->x - child->x) + abs(destination->y - child->y);
					child->f = child->h + child->g;
					if(child->state == CLOSED){
						propagate_path_improvements(child);
					}
				}
			}
		}
	}
}


void propagate_path_improvements(Node* node){
	for(int i = 0; i < node->kids.size(); i++){
		if(node->g + node->kids[i]->cost < node->kids[i]->g){
			node->kids[i]->parent = node;
			node->kids[i]->g = node->g + 1;
			node->kids[i]->f = node->kids[i]->g + node->kids[i]->h;
			propagate_path_improvements(node->kids[i]);
		}
	}
}