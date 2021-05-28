#include "String.h"

String::String() {
    /* ALREADY IMPLEMENTED. DO NOT CHANGE. */
}

String::String(char *str) {
    /* ALREADY IMPLEMENTED. DO NOT CHANGE. */

    // str is a null terminated C string.
    // (e.g. ['h','e','l','l','o','\0'])

    char *temp = str;

    while (*temp != '\0') {
        this->characters.insertAtTheEnd(*temp);
        temp++;
    }
}

int String::getLength() const {
    return this->characters.getSize();
    /* TODO */
}

bool String::isEmpty() const {
    return this->characters.isEmpty();
    /* TODO */
}

void String::appendCharacter(char character) {
    this->characters.insertAtTheEnd(character);
    /* TODO */
}

void String::insertCharacter(char character, int pos) {
    Node<char> * temp;
    if(pos == 0 && this->characters.isEmpty()){
        temp = this->characters.getDummyTail();
    }
    else{
        temp = this->characters.getNodeAtIndex(pos);
    }
    if (temp != NULL){
        this->characters.insertBeforeGivenNode(character,temp);
    }
    /* TODO */
}

void String::eraseCharacters(int pos, int len) {
    Node<char> *tempintempi=NULL, * temp = this->characters.getNodeAtIndex(pos);
    if (this->characters.getSize() >= pos+len){
        for (int i = 0; i < len; i++){
            tempintempi = temp->next;
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;
            temp = tempintempi;
        }
    }
    /* TODO */
}

void String::eraseAllCharacters() {
    this->characters.deleteAllNodes();
    /* TODO */
}

String String::substring(int pos, int len) {
    Node<char> * temp = this->characters.getNodeAtIndex(pos);
    String newStr;
    if (this->characters.getSize() >= pos+len){
        for (int i = 0; i < len; i++){
            newStr.characters.insertAtTheEnd(temp->data);
            temp = temp->next;
        }
    }
    return newStr;
    /* TODO */
}

LinkedList<String> String::split(char separator) {
    String str1;
    LinkedList<String> splited;
    Node<char> * temp = this->characters.getActualHead();
    while (temp != this->characters.getDummyTail()){
        if (temp->data == separator){
            if (str1.isEmpty()){
                Node<String> * newNode = new Node<String>;
                newNode->prev = splited.getDummyTail()->prev;
                newNode->next = splited.getDummyTail()->prev->next;
                newNode->prev->next = newNode;
                newNode->next->prev = newNode;
            }
            else{
                splited.insertAtTheEnd(str1);
                str1.eraseAllCharacters();
            }
        }
        else{
            str1.characters.insertAtTheEnd(temp->data);
        }
        temp = temp->next;
    }
    if (!str1.isEmpty()){
        splited.insertAtTheEnd(str1);
    }
    return splited;
}

bool String::isPalindrome() const {
    Node<char> *straight = this->characters.getActualHead(),*backward = this->characters.getActualTail();
    int size = this->characters.getSize();
    for (int i = 0; i < size/2; i++){
        if (straight->data == 32 || backward->data == 32){
            
        }
        else if (straight->data != backward->data){
            return false;
        }
        straight = straight->next;
        backward = backward->prev;
    }
    return true;
    /* TODO */
}

bool String::operator<(const String &rhs) const {
    Node<char> * left = this->characters.getActualHead(),*right = rhs.characters.getActualHead();
    while (left != this->characters.getDummyTail() && right != rhs.characters.getDummyTail()){
        if ((int)left->data < (int)right->data){
            return true;
        }
        else if ((int)left->data > (int)right->data){
            return false;
        }
        else{
            left = left->next;
            right = right->next;
        }
    }
    if (this->characters.getSize() < rhs.characters.getSize()){
        return true;
    }
    else{
        return false;
    }
    
    
    /* TODO */
}

void String::print(bool verbose) {
    /* ALREADY IMPLEMENTED. DO NOT CHANGE. */

    Node<char> *node = this->characters.getActualHead();
    Node<char> *actualTailNode = this->characters.getActualTail();

    if (verbose) {
        std::cout << "[";
    }

    while (node && node->next) {
        if (verbose) {
            std::cout << "'" << node->data << "'";
            if (node != actualTailNode) {
                std::cout << ",";
            }
        } else {
            std::cout << node->data;
        }

        node = node->next;
    }

    if (verbose) {
        std::cout << "]";
    }

    std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &os, const String &string) {
    /* ALREADY IMPLEMENTED. DO NOT CHANGE. */

    Node<char> *node = string.characters.getActualHead();

    while (node && node->next) {
        os << node->data;
        node = node->next;
    }

    return os;
}
