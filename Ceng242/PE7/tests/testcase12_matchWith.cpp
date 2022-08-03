#include "submain.h"

int main() {

	Edge* edge1 = new StraightEdge(123456);
	Edge* edge2 = new StraightEdge(432157);
	Edge* edge3 = new StraightEdge(513246);

	cout << (edge1->matchWith(*edge2) ? "true" : "false") << endl;		// true
	cout << edge1->getMatchingEdge()->getId() << endl;					// 432157
	cout << edge2->getMatchingEdge()->getId() << endl;					// 123465

	edge2->breakMatch();

	cout << (edge1->matchWith(*edge3) ? "true" : "false") << endl;		// true
	cout << edge1->getMatchingEdge()->getId() << endl;					// 513246
	Edge* edge = edge2->getMatchingEdge();
	if (edge == NULL)
		cout << "no partner" << endl;
	cout << edge3->getMatchingEdge()->getId() << endl;					// 123465

	delete edge1;
	delete edge2;
	delete edge3;

	return 0;
}