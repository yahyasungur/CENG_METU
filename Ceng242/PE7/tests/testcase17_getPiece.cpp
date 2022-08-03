#include "submain.h"

int main() {

	Puzzle* puzzle = new Puzzle(4, 2, 2);
	
	try {
		int location[2] = {3, 3};
		const Piece& piece = puzzle->getPiece(location);
	}
	catch(exception& e) {
		cout << e.what() << endl;
	}

	delete puzzle;

	return 0;
}