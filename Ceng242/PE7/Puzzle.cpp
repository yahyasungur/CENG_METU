#include "Puzzle.h"

vector<const Puzzle*> puzzles;
vector<const Piece*> pieces;
static int k = 1;
/****************************************************/
/****              *** PUZZLE ***                ****/

/* Contsructor : It takes three integers in the following order:
    The first argument is size of the puzzle which is 2^N for some N >= 0.
    The second argument is the initial row id of the puzzle.
    The third argument is the initial column id of the puzzle.
    
    After initialization with the above arguments, the necessary 
    pointers should be initialized to NULL.
    Note that the final row id in this puzzle is equal to: 
    initial_row_id + size - 1.
    Note that the final column id in this puzzle is equal to: 
    initial_column_id + size - 1.
    
    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required. 
*/
Puzzle::Puzzle(int N, int row, int column) {
    // TODO
    this->size = N;
    this->first_row = row;
    this->first_column = column;
    this->piece = NULL;
    this->top_right = NULL;
    this->top_left = NULL;
    this->bottom_left = NULL;
    this->bottom_right = NULL;
}

/* Destructor  : It should destruct its sub-puzzles, yet it is NOT responsible
of the destruction of its Piece member.
*/

void Puzzle::destruct(Puzzle* puzzle, int siz){
    if (puzzle == NULL){
        return;
    }
/*     siz = (unsigned) siz;

    if (siz <= 1){
        //delete puzzle;
        //puzzle->piece->~Piece();
        return;
    } */

    /* top_left */
    this->destruct(puzzle->top_left, siz/2);
    if(puzzle->top_left != NULL){
        delete puzzle->top_left;
    }

    /* top_right */
    this->destruct(puzzle->top_right, siz/2);
    if(puzzle->top_right != NULL){
        delete puzzle->top_right;
    } 

    /* bottom_left */
    this->destruct(puzzle->bottom_left, siz/2);
    if(puzzle->bottom_left != NULL){
        delete puzzle->bottom_left;
    }

    /* bottom_right */
    this->destruct(puzzle->bottom_right, siz/2);
    //if(puzzle->bottom_right != NULL) delete puzzle->bottom_right;
    
    return;
}

void dest(){
    if (k){
        k--;
        for (unsigned int i = 0; i < puzzles.size(); i++){
            if (puzzles[i] != NULL){
                delete puzzles[i];
                puzzles[i] = NULL;
            }
        }
    }
}

Puzzle::~Puzzle() {
    // TODO
    //destruct(this, this->size);
    //if (this->top_left != NULL) delete this->top_left;
    //if (this->top_right != NULL) delete this->top_right;
    //if (this->bottom_left != NULL) delete this->bottom_left;
    //if (this->bottom_right != NULL) delete this->bottom_right;
    
    /*for (unsigned int i = 0; i < puzzles.size(); i++){
        if (puzzles[i] != NULL){
            delete puzzles[i];
            puzzles[i] = NULL;
        }
    } */
    if (k){
        dest();
    }

    for (unsigned int i = 0; i < pieces.size(); i++){
        if (pieces[i] != NULL){
            delete pieces[i];
            pieces[i] = NULL;
        }
    }
    pieces.clear();
}

/* Copy constructor : It totally applies deep copy except the Piece
member part. Do not deep copy Piece objects of the puzzle, instead
do shallow copy for Pieces.
*/
Puzzle::Puzzle(const Puzzle& p) {
    // TODO
    this->top_left = p.top_left;
    this->top_right = p.top_right;
    this->bottom_left = p.bottom_left;
    this->bottom_right = p.bottom_right;
    this->size = p.size;
    this->first_column = p.first_column;
    this->first_row = p.first_row;
    this->piece = p.piece;
}

/* Assignment operator : It totally applies shallow copy.
*/

Puzzle& Puzzle::operator=(const Puzzle& p) {
    // TODO
    this->top_left = p.top_left;
    this->top_right = p.top_right;
    this->bottom_left = p.bottom_left;
    this->bottom_right = p.bottom_right;
    this->size = p.size;
    this->first_column = p.first_column;
    this->first_row = p.first_row;
    this->piece = p.piece;
    return *this;
}

/* This method directly assigns (without copying) the given Piece object to
    the corresponding sub-puzzle (cell) whose indices given in the second 
    argument in array form as follows <row_id, column_id>.

    ATTENTION: If a sub-puzzle member does not include any Piece, namely, 
    if its piece is NULL, then do NOT construct it. In other words, do 
    NOT construct subpuzzles unless they are required.
*/

void Puzzle::placePiece_helper(Puzzle* puzzle , const Piece& piece,int row, int column, int f_row, int f_column, int size){
    if (size == 1){
        puzzle->first_column = f_column;
        puzzle->first_row = f_row;
        puzzle->top_left = NULL;
        puzzle->bottom_left = NULL;
        puzzle->top_right = NULL;
        puzzle->bottom_right = NULL;
        puzzle->size = 1;
        puzzle->piece = new Piece(piece);
        pieces.push_back(puzzle->piece);
        return;
    }
    
    if (row < f_row + (size/2) && column < f_column + (size/2)){
        /* top_left */
        if (puzzle->top_left == NULL){
            puzzle->top_left = new Puzzle(size/2, f_row, f_column);
            puzzles.push_back(puzzle->top_left);
        }
        return placePiece_helper(puzzle->top_left, piece, row, column, f_row, f_column, size/2);
    }
    else if (row < f_row + (size/2) && column >= f_column + (size/2)){
        /* top_right */
        if (puzzle->top_right == NULL){
            puzzle->top_right = new Puzzle(size/2, f_row, f_column+(size/2));
            puzzles.push_back(puzzle->top_right);
        }
        return placePiece_helper(puzzle->top_right, piece, row, column, f_row, f_column+(size/2), size/2);
    }
    else if (row >= f_row + (size/2) && column < f_column + (size/2)){
        /* bottom_left */
        if (puzzle->bottom_left == NULL){
            puzzle->bottom_left = new Puzzle(size/2, f_row+(size/2), f_column);
            puzzles.push_back(puzzle->bottom_left);
        }
        return placePiece_helper(puzzle->bottom_left, piece, row, column, f_row+(size/2), f_column, size/2);
    }
    else if (row >= f_row + (size/2) && column >= f_column + (size/2)){
        /* bottom_right */
        if (puzzle->bottom_right == NULL){
            puzzle->bottom_right = new Puzzle(size/2, f_row+(size/2), f_column+(size/2));
            puzzles.push_back(puzzle->bottom_right);
        }
        return placePiece_helper(puzzle->bottom_right, piece, row, column, f_row+(size/2), f_column+(size/2), size/2);
    }
}

void Puzzle::placePiece(const Piece& piece, int coordinates[2]) {
    // TODO
    int row = coordinates[0];
    int column = coordinates[1];
    int size = this->size;

    int i = size/2;

    if (row < i + this->first_row && column < i + this->first_column){
        /* top_left */
        if (this->top_left == NULL){
            this->top_left = new Puzzle(size/2, this->first_row, this->first_column);
            puzzles.push_back(this->top_left);
        }
        placePiece_helper(this->top_left, piece, row, column, this->first_row, this->first_column, size/2);
    }
    else if (row < i + this->first_row && column >= i + this->first_column){
        /* top_right */
        if (this->top_right == NULL){
            this->top_right = new Puzzle(size/2, this->first_row, this->first_column+(size/2));
            puzzles.push_back(this->top_right);
        }
        placePiece_helper(this->top_right, piece, row, column, this->first_row, this->first_column+(size/2), size/2);
    }
    else if (row >= i + this->first_row && column < i + this->first_column){
        /* bottom_left */
        if (this->bottom_left == NULL){
            this->bottom_left = new Puzzle(size/2, this->first_row+(size/2), this->first_column);
            puzzles.push_back(this->bottom_left);
        }
        placePiece_helper(this->bottom_left, piece, row, column, this->first_row+(size/2), this->first_column, size/2);
    }
    else if (row >= i + this->first_row && column >= i + this->first_column){
        /* bottom_right */
        if (this->bottom_right == NULL){
            this->bottom_right = new Puzzle(size/2, this->first_row+(size/2), this->first_column+(size/2));
            puzzles.push_back(this->bottom_right);
        }
        placePiece_helper(this->bottom_right, piece, row, column, this->first_row+(size/2), this->first_column+(size/2), size/2);
    }
}

/* It returns directly the piece object located in the sub-puzzle (cell)
    whose row id and column id are given in the first and second elements of 
    2D array as argument, respectively. If there is no piece in the requested 
    indices, then this method throws an EmptyCellRequest exception defined in 
    Exception.h file.
*/

const Piece* piieeccee = NULL;
void Puzzle::getPiece_helper(const Puzzle* puzzle,int row, int column, int f_row, int f_column, int size) const{
    if (puzzle == NULL){
        piieeccee = NULL;
        return;
    }

    if (size == 1){
        piieeccee = puzzle->piece;
        return;
    }
    
    if (row < f_row + (size/2) && column < f_column + (size/2)){
        /* top_left */
        getPiece_helper(puzzle->top_left, row, column, f_row, f_column, size/2);
    }
    else if (row < f_row + (size/2) && column >= f_column + (size/2)){
        /* top_right */
        getPiece_helper(puzzle->top_right, row, column, f_row, f_column+(size/2), size/2);
    }
    else if (row >= f_row + (size/2) && column < f_column + (size/2)){
        /* bottom_left */
        getPiece_helper(puzzle->bottom_left, row, column, f_row+(size/2), f_column, size/2);
    }
    else if (row >= f_row + (size/2) && column >= f_column + (size/2)){
        /* bottom_right */
        getPiece_helper(puzzle->bottom_right, row, column, f_row+(size/2), f_column+(size/2), size/2);
    }
}

const Piece& Puzzle::getPiece(int coordinates[2]) const {
    // TODO
    piieeccee = NULL;
    getPiece_helper(this, coordinates[0], coordinates[1], this->first_row, this->first_column, this->size);
    if (piieeccee == NULL){
        throw EmptyCellRequest();
    }
    else{
        return *piieeccee;
    }
    
}

/* This method returns the sub-puzzle whose initial and final row-column ids 
are given in the first and second arguments, respectively. The indices
given in the arguments will be given as an exact correspondence to one of
the sub-puzzles of the current puzzle object.

ATTENTION: The sub-puzzle to be cropped may correspond to a NULL part of the
Puzzle object. In that case, it is enough to you to create a new Puzzle 
object that satisfies the asked properties and return it. OF course, do NOT 
forget to do this operation by escaping from memory leaks!!!
*/

const Puzzle* Puzzle::give_me_pointer_at_index(const Puzzle* puzzle, int row, int column, int f_row, int f_column, int size, int sz) const{
    
    if (puzzle == NULL){
        //puzzle = new Puzzle(size, f_row, f_column);
        //puzzles.push_back(puzzle);
        return NULL;
    }

    if (f_row == row && f_column == column && size == sz/2){
        return puzzle;
    }
    else if (row < f_row + (size/2) && column < f_column + (size/2)){
        /* top_left */
        return give_me_pointer_at_index(puzzle->top_left, row, column, f_row, f_column, size/2, sz);
    }
    else if (row < f_row + (size/2) && column >= f_column + (size/2)){
        /* top_right */
        return give_me_pointer_at_index(puzzle->top_right, row, column, f_row, f_column+(size/2), size/2, sz);
    }
    else if (row >= f_row + (size/2) && column < f_column + (size/2)){
        /* bottom_left */
        return give_me_pointer_at_index(puzzle->bottom_left, row, column, f_row+(size/2), f_column, size/2, sz);
    }
    else if (row >= f_row + (size/2) && column >= f_column + (size/2)){
        /* bottom_right */
        return give_me_pointer_at_index(puzzle->bottom_right, row, column, f_row+(size/2), f_column+(size/2), size/2 , sz);
    }
}

Puzzle Puzzle::crop(int from[2], int to[2]) const {
    // TODO
    int sz = to[0] - from[0] + 1;
    int f_row = from[0];
    int f_column = from[1];
    
    const Puzzle *t_l, *t_r, *b_l, *b_r;
    t_l = give_me_pointer_at_index(this, from[0], from[1], this->first_row, this->first_column, this->size, sz);
    t_r = give_me_pointer_at_index(this, from[0], from[1]+(sz/2), this->first_row, this->first_column, size, sz);
    b_l = give_me_pointer_at_index(this, from[0]+(sz/2), from[1], this->first_row, this->first_column, size, sz);
    b_r = give_me_pointer_at_index(this, from[0]+(sz/2), from[1]+(sz/2), this->first_row, this->first_column, size, sz);

    Puzzle* p = new Puzzle(sz, f_row, f_column);
    p->top_left = const_cast<Puzzle*> (t_l);
    p->top_right = const_cast<Puzzle*> (t_r);
    p->bottom_left = const_cast<Puzzle*> (b_l);
    p->bottom_right = const_cast<Puzzle*> (b_r);

    puzzles.push_back(p);

    return *p;
}

/****************************************************/
/*        THE BELOW PART WILL NOT BE GRADED.        */
/*      YOU CAN IMPLEMENT IF YOU WOULD LIKE TO.     */
/****************************************************/
/*
    This method puts (patches) the given puzzle onto the corresponding part
    of the current puzzle object. To which part it will be patched on could
    be determined by just checking the initial row-column indices and the size
    of the puzzle given in the argument. 
    Unlike crop() method, the puzzle given in the argument may not be an exact 
    correspondence of some sub-puzzle. It is ensured that the given argument will
    be located on some sub-space of the current puzzle, yet it may *partially* 
    overlap with some or more sub-puzzles (See the figure in the pdf).
    The patch operation requires deep-copy of the corresponding sub-puzzles
    whereas it requires shallow copy of the corresponding Piece objects.
    
    HINT: You may get benefit from placePiece() method and you may start your
    operation by clearing the corresponding parts of the current puzzle.
*/
void Puzzle::patch(const Puzzle&) {
    // TODO
}

