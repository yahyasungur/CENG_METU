#include "submain.h"

int main() {

	Piece* pieces[256];
	for (int i=0; i<256; i++) {
		StraightEdge edge1(i*4);
		StraightEdge edge2(i*4 + 1);
		StraightEdge edge3(i*4 + 2);
		StraightEdge edge4(i*4 + 3);
		Edge* edges[4] = {&edge1, &edge2, &edge3, &edge4};

		pieces[i] = new Piece(edges);
	}

	Puzzle* puzzle = new Puzzle(16, 0, 0);
	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) {
			int location[2] = {i, j};
			puzzle->placePiece(*pieces[j*16 + i], location);
		}
	}

	cout << *puzzle << endl;

	for (int i=0; i<256; i++)
		delete pieces[i];
	delete puzzle;

	return 0;
}