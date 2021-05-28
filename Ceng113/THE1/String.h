#ifndef STRING_H
#define STRING_H

#include <iostream>

#include "LinkedList.h"

class String {
public: // DO NOT CHANGE THIS PART.
    String();
    String(char *str);

    int getLength() const;
    bool isEmpty() const;

    void appendCharacter(char character);
    void insertCharacter(char character, int pos);

    void eraseCharacters(int pos, int len);
    void eraseAllCharacters();

    String substring(int pos, int len);

    LinkedList<String> split(char separator);

    bool isPalindrome() const;

    bool operator<(const String &rhs) const;

    void print(bool verbose=false);

    friend std::ostream &operator<<(std::ostream &os, const String &string);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    LinkedList<char> characters;
};

#endif //STRING_H
