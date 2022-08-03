#include "submain.h"

int main() {
	
	Edge* edge1 = new InwardsEdge(123456);
	Edge* edge2 = new OutwardsEdge(432157);
	Edge* edge3 = new StraightEdge(513246);
	Edge* edge4 = new StraightEdge(654327);
	Edge* edge5 = new OutwardsEdge(562258);
	Edge* edge6 = new InwardsEdge(957585);

	CompositeEdge* edge7 = new CompositeEdge(87653487);
	CompositeEdge* edge8 = new CompositeEdge(15121304);
	edge7->addEdge(edge1)->addEdge(edge3)->addEdge(edge5);
	edge8->addEdge(edge2)->addEdge(edge4)->addEdge(edge6);

	cout << (edge7->matchWith(*edge8) ? "true" : "false") << endl;		// true
	cout << edge7->getMatchingEdge()->getId() << endl;					// 15121304
	cout << edge8->getMatchingEdge()->getId() << endl;					// 87653487
	edge8->breakMatch();
	
	Edge* edge9 = new OutwardsEdge(561258);
	Edge* edge10 = new StraightEdge(847199);
	Edge* edge11 = new InwardsEdge(448486);

	CompositeEdge* edge12 = new CompositeEdge(95785521);
	edge12->addEdge(edge9)->addEdge(edge10)->addEdge(edge11);
	edge1->matchWith(*edge9);
	edge3->matchWith(*edge10);
	edge5->matchWith(*edge11);
	cout << (edge7->matchWith(*edge12) ? "true" : "false") << endl;		// true
	cout << edge7->getMatchingEdge()->getId() << endl;					// 95785521
	cout << edge12->getMatchingEdge()->getId() << endl;					// 87653487

	delete edge7;
	delete edge8;
	delete edge12;
	return 0;
}