#include "vector.h"
#include "stack.h"
#include <set>

struct coordT {
	double x, y;
};

struct arc;

struct node{
	string name;
	coordT loc;
	Vector<arc*> outgoing;
};

struct arc{
	int length;
	node* end1;
	node* end2;
};

struct path
{
	Stack<node> area;
	set<string> walked;
};