#include "submain.h"

int main() {

	Edge* edge1 = new OutwardsEdge(123456);
	Edge* edge2 = new InwardsEdge(432157);
	Edge* edge3 = new InwardsEdge(513246);

	cout << (edge1->matchWith(*edge2) ? "true" : "false") << endl;		// true
	cout << edge1->getMatchingEdge()->getId() << endl;					// 432157
	cout << edge2->getMatchingEdge()->getId() << endl;					// 123465

	edge1->breakMatch();

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