#include "submain.h"

int main() {
	
	Edge* edge1 = new StraightEdge(123456);
	Edge* edge2 = new StraightEdge(432157);

	cout << (edge1->matchWith(*edge2) ? "true" : "false") << endl;		// true
	cout << edge1->getMatchingEdge()->getId() << endl;					// 432157
	cout << edge2->getMatchingEdge()->getId() << endl;					// 123465
	
	delete edge1;
	delete edge2;

	return 0;
}