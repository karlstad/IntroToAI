#include <vector>

enum States {UNKNOWN, OPEN, CLOSED};

struct Node{
	int x, y, g, h, f;
	char value;
	Node* parent;
	States state;

	Node() : x(0), y(0), g(0), h(0), f(0), value(0), parent(NULL), state(UNKNOWN){}
	//bool operator<(const Node& node) {return f < node.f;}
};

Node* findPath(Node** board);
/*void generate_successors(Node** board, std::vector<Node*>* successors, Node* currentNode);
void attach_and_eval(Node* kid, Node* currentNode, Node* destination);
void insert_sorted(std::vector<Node*>* vec, Node* node);
void propagate_path_improvements(Node* node);*/