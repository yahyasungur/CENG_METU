#ifndef CATEGORY_H
#define CATEGORY_H


// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "BinarySearchTree.h"
#include "Book.h"

class Category {
public:
    Category();
    Category(const std::string &name);

    const std::string &getName() const;

    void addBook(const Book &book);
    void removeBook(const Book &book);
    Book *searchBook(const Book &book);
    std::vector<Book *> getListOfBooks();

    bool operator<(const Category &rhs) const;
    bool operator>(const Category &rhs) const;
    bool operator==(const Category &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Category &category);

private:
    std::string name;
    BinarySearchTree<Book> books;
};


#endif //CATEGORY_H
