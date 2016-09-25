#include <vector>

struct Node{
	int x, y, g, h;
	Node* parent;



};

void findPath(char** solution, char** board){
	vector<Node> open;
	vector<Node> closed;
	Node currentNode;
	Node destination;

	for(int x = 0; x < 20; x++){
		for(int y = 0; y < 7; y++){
			if(board[x][y] == 'A'){
				currentNode.x = x;
				currentNode.y = y;
			} else if(board[x][y] == 'B'){
				destination.x = x;
				destination.y = y;
			}

		}
	}
	currentNode.g = 0;
	currentNode.h = destination.x - currentNode.x;
}