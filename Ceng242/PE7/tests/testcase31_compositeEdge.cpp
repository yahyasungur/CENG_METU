#include "submain.h"

int main() {
	
	Edge* edge1 = new InwardsEdge(123456);
	Edge* edge2 = new StraightEdge(513246);
	Edge* edge3 = new OutwardsEdge(562258);

	CompositeEdge* edge4 = new CompositeEdge(87653487);
	edge4->addEdge(edge1)->addEdge(edge2)->addEdge(edge3);

	
	Edge* edge5 = new OutwardsEdge(561258);
	Edge* edge6 = new InwardsEdge(448486);
	Edge* edge7 = new StraightEdge(847199);

	CompositeEdge* edge8 = new CompositeEdge(95785521);
	edge8->addEdge(edge5)->addEdge(edge6)->addEdge(edge7);
	

	cout << (edge4->matchWith(*edge8) ? "true" : "false") << endl;		// false
	
	delete edge4;
	delete edge8;
	return 0;
}