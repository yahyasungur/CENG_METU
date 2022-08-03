#include "Piece.h"

/****************************************************/
/****               *** PIECE ***                ****/
vector<Edge *> clones2;
/* Contsructor : initializes <edges> of the object to the those given in the
argument. The edges given in the argument array should be cloned first,
and its clones should be reserved, not the edges themselves.
Note that the ordering of the given edges will always be as follows:
edges[0]: Left side edge, 
edges[1]: Bottom side edge, 
edges[2]: Right side edge, 
edges[3]: Top side edge.
*/
Piece::Piece(Edge* _edges[4] ) {
    // TODO
    for (int i = 0; i < 4; i++){
        this->edges[i] = _edges[i]->clone();
        clones2.push_back(this->edges[i]);
    }
}

/* Destructor  : It should destruct its edges too.
*/
Piece::~Piece() {
    // TODO
/*     for (int i = 0; i < 4; i++){
        if (this->edges[i] != NULL){
            delete this->edges[i];
            this->edges[i] = NULL;
        }
    } */
    for (unsigned int i = 0; i < clones2.size(); i++){
        if (clones2[i] != NULL){
            delete clones2[i];
            clones2[i] = NULL;
        }
        
    }
    
}

/* Copy constructor : Apply deep copy.
*/
Piece::Piece(const Piece& piece) {
    // TODO
    for (int i = 0; i < 4; i++){
        this->edges[i] = piece.edges[i];
    }
    
}

// This is already implemented for you, do NOT change it!
ostream& operator<< (ostream& os, const Piece& piece) {

	for (int i = 0; i < 4; i++)
		os << piece.edges[i]->getId() << "  \n";
	return os;
}
