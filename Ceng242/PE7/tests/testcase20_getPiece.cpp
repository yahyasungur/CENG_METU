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
			// place piece
			int location[2] = {i, j};
			puzzle->placePiece(*pieces[j*16 + i], location);

			// get piece
			try {
				int location[2] = {j, i};
				const Piece& piece = puzzle->getPiece(location);
				cout << "The following piece has been found:" << endl;
				cout << piece << endl;
			}
			catch(exception& e) {
				cout << e.what() << endl << endl;
			}
		}
	}

	cout << *puzzle << endl;

	for (int i=0; i<256; i++)
		delete pieces[i];
	delete puzzle;

	return 0;
}