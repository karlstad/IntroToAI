#include <vector>

#define BOARD_WIDTH 40
#define BOARD_HEIGTH 10

enum States {UNKNOWN, OPEN, CLOSED};

struct Node{
	int x, y, g, h, f, cost;
	char value;
	Node* parent;
	States state;
	std::vector<Node*> kids;


	Node() : x(0), y(0), g(0), h(0), f(0), value(0), parent(NULL), state(UNKNOWN){}
};

Node* findPath_AStar(Node** board);
Node* findPath_BFS(Node** board);
Node* findPath_Dijkstra(Node** board);
void propagate_path_improvements(Node* node);