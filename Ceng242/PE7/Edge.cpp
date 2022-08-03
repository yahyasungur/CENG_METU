#include "Edge.h"


vector<Edge *> clones;
static int ind = 1;

/****************************************************/
/****                *** EDGE ***                ****/

/* Contsructor : initializes <id> of the object to the given integer
and <password> of the object to the given Password object.   
*/
Edge::Edge(int _id, Password _password) {
    // TODO
    this->id = _id;
    this->password = _password;
    this->matchingEdge = NULL;
}

/* Destructor  : It is NOT responsible of the destruction of the matchingEdge!
*/
void des(){
    if (ind){
        ind--;
        for (unsigned int i = 0; i < clones.size(); i++){
            if (clones[i] != NULL){
                //delete clones[i];
                //clones[i] = NULL;
            }
        }
    }
}

Edge::~Edge() {
    // TODO
/*     for (unsigned int i = 0; i < clones.size(); i++){
        if (clones[i] != NULL){
            delete clones[i];
            clones[i] = NULL;
        }
    } */
    if (ind){
        des();
    }
    //clones.clear();
}

/* Returns the <id> of the object
*/
int Edge::getId() const {
	// TODO
    return this->id;
}

/* Returns the pointer to the matching partner of the current edge.
If the edge had not been matched before, it returns NULL.
*/
Edge* Edge::getMatchingEdge() const {
    // TODO
    return this->matchingEdge;
}

/* It tries to match the current Edge object with the one given in the argument.
If the two edges are matchable then it does the matching by storing
<matchingEdge> variables with each other, and returns true. Otherwise,
it does not match and returns false.
It applies the matching rules given in the pdf.
Note that match operation is a mutual operation. Namely, if the current
edge is matched, then its partner edge should be matched with the current 
one too.
HINT: It may need matchWithHelper(Password) method.

Note: Of course, it would be nicer to overload this method for taking 
different types of Edges as arguments, yet this design was preffered 
specifically for you to discover mechanism of virtual. Helper method
is given to the issue.
*/
bool Edge::matchWith(Edge& _edge) {
    // TODO
    if (this->password == SEND_ME_STRAIGHT && _edge.password == SEND_ME_STRAIGHT){
        this->breakMatch();
        _edge.breakMatch();

        this->matchingEdge = &_edge;
        _edge.matchingEdge = this;
        return true;
    }
    else if (this->password == SEND_ME_OUTWARDS && _edge.password == SEND_ME_INWARDS){
        this->breakMatch();
        _edge.breakMatch();
        
        this->matchingEdge = &_edge;
        _edge.matchingEdge = this;
        return true;
    }
    else if (this->password == SEND_ME_INWARDS && _edge.password == SEND_ME_OUTWARDS){
        this->breakMatch();
        _edge.breakMatch();
        
        this->matchingEdge = &_edge;
        _edge.matchingEdge = this;
        return true;
    }

    return false;
}

/* If the current edge was matched with some edge before, then this method
breaks the match, i.e. there is no match between those two edges anymore.
Note that breaking match operation is a mutual operation. Namely, if the 
matching of the current edge is broken, the matching recorded in its partner 
edge should be broken too.
*/
void Edge::breakMatch() {
    // TODO
    if (this->matchingEdge != NULL){
        this->matchingEdge->matchingEdge = NULL;
        this->matchingEdge = NULL;
    }
}

/****************************************************/
/****            *** STRAIGHT EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
and <password> of the object.
Note that Password variable has a fixed value which is SEND_ME_STRAIGHT,
therefore it is not given as an argument.
*/
StraightEdge::StraightEdge(int _id):Edge(_id, SEND_ME_STRAIGHT) {
	// TODO
    this->matchingEdge = NULL;
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
StraightEdge::~StraightEdge() {
    // TODO
}

/* This method clones the current object and returns the pointer to its clone.
Cloning is actually a deep-copy operation, so you need to construct a new
StraightEdge object.
Note that if the current edge is matched with some other edge, then its
matchingEdge should be cloned too and only the clones should be matched 
with each other.
*/
Edge* StraightEdge::clone() const {
    // TODO
    StraightEdge *_newedge = new StraightEdge(this->id);
    if (this->matchingEdge != NULL){
        _newedge->matchingEdge = this->matchingEdge;
    }
    clones.push_back(_newedge);

    return _newedge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool StraightEdge::matchWithHelper(Password) {
    // TODO
    return true;
}

/****************************************************/
/****            *** INWARDS EDGE ***            ****/

/* Contsructor : initializes <id> of the object to the given integer
and <password> of the object.
Note that Password variable has a fixed value which is SEND_ME_OUTWARDS,
therefore it is not given as an argument.
*/
InwardsEdge::InwardsEdge(int _id):Edge(_id, SEND_ME_INWARDS) {
    // TODO
    this->matchingEdge = NULL;
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
InwardsEdge::~InwardsEdge() {
    // TODO
}

/* This method clones the current object and returns the pointer to its clone.
Cloning is actually a deep-copy operation, so you need to construct a new
InwardsEdge object.
Note that if the current edge is matched with some other edge, then its
matchingEdge should be cloned too and only the clones should be matched 
with each other.
*/
Edge* InwardsEdge::clone() const {
    // TODO
    InwardsEdge *_newedge = new InwardsEdge(this->id);
    if (this->matchingEdge != NULL){
        _newedge->matchingEdge = this->matchingEdge;
    }
    clones.push_back(_newedge);

    return _newedge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool InwardsEdge::matchWithHelper(Password) {
    // TODO
    return true;
}

/****************************************************/
/****            *** OUTWARDS EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
and <password> of the object.
Note that Password variable has a fixed value which is SEND_ME_INWARDS,
therefore it is not given as an argument.
*/
OutwardsEdge::OutwardsEdge(int _id):Edge(_id, SEND_ME_OUTWARDS) {
    // TODO
    this->matchingEdge = NULL;
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
OutwardsEdge::~OutwardsEdge() {
    // TODO
}

/* This method clones the current object and returns the pointer to its clone.
Cloning is actually a deep-copy operation, so you need to construct a new
OutwardsEdge object.
Note that if the current edge is matched with some other edge, then its
matchingEdge should be cloned too and only the clones should be matched 
with each other.
*/
Edge* OutwardsEdge::clone() const {
    // TODO
    OutwardsEdge *_newedge = new OutwardsEdge(this->id);
    if (this->matchingEdge != NULL){
        _newedge->matchingEdge = this->matchingEdge;
    }
    clones.push_back(_newedge);

    return _newedge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool OutwardsEdge::matchWithHelper(Password) {
	// TODO
    return true;
}

/****************************************************/
/*        THE BELOW PART WILL NOT BE GRADED.        */
/*      YOU CAN IMPLEMENT IF YOU WOULD LIKE TO.     */
/****************************************************/

/****************************************************/
/****            *** COMPOSITE EDGE ***          ****/

/* Contsructor : initializes <id> of the object to the given integer
and <password> of the object.
Note that Password variable has a fixed value which is SEND_ME_COMPLETING_COMPOSITE,
therefore it is not given as an argument.
Note that you may need to initialize matchIndex variable with some value
so that you may benefit from that during any match operation.
*/
CompositeEdge::CompositeEdge(int _id):Edge(_id, SEND_ME_COMPLETING_COMPOSITE) {
	// TODO
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
However, it should delete its member edges too.
*/
CompositeEdge::~CompositeEdge() {
	// TODO
}

/* This method clones the current object and returns the pointer to its clone.
Cloning is actually a deep-copy operation, so you need to construct a new
CompositeEdge object. During the construction, each member Edge object 
should be cloned too, and the clone of the current CompositeEdge should
include only the clones of the member edges.
Note that if the current edge is matched with some other edge, then its
matchingEdge should be cloned too and only the clones should be matched 
with each other.
*/
Edge* CompositeEdge::clone() const {
    // TODO
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool CompositeEdge::matchWithHelper(Password) {
	// TODO
}

/* It tries to match the current CompositeEdge object with the one given in the 
argument.
If the two edges are matchable then it does the matching by storing
<matchingEdge> variables with each other, and returns true. Otherwise,
it does not match and returns false.
It applies the matching rules given in the pdf.
Note that match operation is a mutual operation. Namely, if the current
edge is matched, then its partner edge should be matched with the current 
one too.
HINT: It may need matchWithHelper(Password) method.

Note: Of course, it would be nicer to overload this method for taking 
different types of Edges as arguments, yet this design was preffered 
specifically for you to discover mechanism of virtual. Helper method
is given to the issue.
*/
bool CompositeEdge::matchWith(Edge&) {
    // TODO
}

/* If the current edge was matched with some edge before, then this method
breaks the match, i.e. there is no match between those two edges anymore.
Note that breaking match operation is a mutual operation. Namely, if the 
matching of the current edge is broken, the matching recorded in its partner 
edge should be broken too.
*/
void CompositeEdge::breakMatch() {
    // TODO
}

/* This method pushes back the given edge in the argument into the end of the 
member edges vector.
*/
CompositeEdge* CompositeEdge::addEdge(Edge* edge) {
    // TODO
}
