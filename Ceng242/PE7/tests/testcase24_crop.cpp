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
		}
	}

	int from[2] = {8, 8};
	int to[2] = {11, 11};
	Puzzle cropped_part = puzzle->crop(from, to);
	cout << cropped_part << endl << endl; 

	int from2[2] = {10, 8};
	int to2[2] = {11, 9};
	Puzzle cropped_part2 = cropped_part.crop(from2, to2);
	cout << cropped_part2 << endl << endl; 
	cout << cropped_part << endl << endl; 
	cout << *puzzle << endl << endl;

	for (int i=0; i<256; i++)
		delete pieces[i];
	delete puzzle;

	return 0;
}