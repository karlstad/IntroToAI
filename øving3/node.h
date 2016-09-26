#include <vector>

enum States {UNKNOWN, OPEN, CLOSED};

struct Node{
	int x, y, g, h, f;
	char value;
	Node* parent;
	std::vector<Node*> kids;
	States state;

	Node() : x(0), y(0), g(0), h(0), f(0), value(0), parent(NULL), state(UNKNOWN){}
};

struct Board{
	Node** board;
	Node solutionNode;
	std::vector<Node> open;
	std::vector<Node> closed;
	std::vector<Node> successors;
};

Node* findPath(Node** board);
void generate_successors(Node** board, std::vector<Node*>* successors, Node* currentNode);
void attach_and_eval(Node* kid, Node* currentNode, Node* destination);
void insert_sorted(std::vector<Node*>* vec, Node* node);
void propagate_path_improvements(Node* node);