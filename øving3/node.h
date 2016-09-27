#include <vector>

#define BOARD_WIDTH 20
#define BOARD_HEIGTH 7

enum States {UNKNOWN, OPEN, CLOSED};

struct Node{
	int x, y, g, h, f, cost;
	char value;
	Node* parent;
	States state;


	Node() : x(0), y(0), g(0), h(0), f(0), value(0), parent(NULL), state(UNKNOWN){}
	//bool operator<(const Node& node) {return f < node.f;}
};

Node* findPath(Node** board);
//void propagate_path_improvements(Node* node);