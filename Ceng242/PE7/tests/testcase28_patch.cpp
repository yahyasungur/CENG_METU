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


	// Piece-1
	StraightEdge edge1(1111);
	InwardsEdge edge2(2222);
	InwardsEdge edge3(3333);
	OutwardsEdge edge4(4444);
	Edge* edges1[4] = {&edge1, &edge2, &edge3, &edge4};

	Piece* piece1 = new Piece(edges1);

	// Piece-2
	InwardsEdge edge5(5555);
	OutwardsEdge edge6(6666);
	OutwardsEdge edge7(7777);
	InwardsEdge edge8(8888);
	Edge* edges2[4] = {&edge5, &edge6, &edge7, &edge8};

	Piece* piece2 = new Piece(edges2);

	// Piece-3
	StraightEdge edge9(9999);
	InwardsEdge edge10(1010);
	OutwardsEdge edge11(1011);
	StraightEdge edge12(1012);
	Edge* edges3[4] = {&edge9, &edge10, &edge11, &edge12};

	Piece* piece3 = new Piece(edges3);

	// Piece-4
	InwardsEdge edge13(1013);
	OutwardsEdge edge14(1014);
	OutwardsEdge edge15(1015);
	InwardsEdge edge16(1016);
	Edge* edges4[4] = {&edge13, &edge14, &edge15, &edge16};
	
	Piece* piece4 = new Piece(edges4);

	// Patch-1
	Puzzle* patch1 = new Puzzle(4, 6, 6);

	int location1[2] = {6, 6};
	patch1->placePiece(*piece1, location1);

	int location2[2] = {9, 9};
	patch1->placePiece(*piece2, location2);

	puzzle->patch(*patch1);
	cout << *puzzle << endl << endl;

	// Patch-2
	Puzzle* patch2 = new Puzzle(8, 3, 5);

	int location3[2] = {4, 6};
	patch2->placePiece(*piece3, location3);

	int location4[2] = {7, 11};
	patch2->placePiece(*piece4, location4);

	puzzle->patch(*patch2);
	cout << *puzzle << endl;

	for (int i=0; i<256; i++)
		delete pieces[i];
	delete piece1;
	delete piece2;
	delete piece3;
	delete piece4;
	delete patch1;
	delete patch2;
	delete puzzle;

	return 0;
}