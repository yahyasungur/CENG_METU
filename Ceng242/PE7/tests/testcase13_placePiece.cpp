#include "submain.h"

int main() {

	StraightEdge edge1(1111);
	InwardsEdge edge2(2222);
	InwardsEdge edge3(3333);
	OutwardsEdge edge4(4444);
	Edge* edges[4] = {&edge1, &edge2, &edge3, &edge4};

	Piece* piece = new Piece(edges);

	Puzzle* puzzle = new Puzzle(2, 0, 0);
	int location[2] = {0, 1};
	puzzle->placePiece(*piece, location);
	cout << *puzzle << endl;

	delete piece;
	delete puzzle;

	return 0;
}