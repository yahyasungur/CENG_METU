#ifndef BOOKCATALOG_H
#define BOOKCATALOG_H


#include <iostream>
#include <vector>

#include "BinarySearchTree.h"
#include "Category.h"

class BookCatalog {
public: // DO NOT CHANGE THIS PART.
    BookCatalog();

    const BinarySearchTree<Category> &getCategories() const;

    void addCategory(const std::string &categoryName);
    void removeCategory(const std::string &categoryName);
    Category *searchCategory(const std::string &categoryName);

    void addBook(const std::string &categoryName, const Book &book);
    void removeBookByIsbn(const std::string &isbn);
    void removeBookByTitle(const std::string &title);
    Book *searchBookByIsbn(const std::string &isbn);
    Book *searchBookByTitle(const std::string &title);

    std::vector<Book *> getListOfBooksByCategory(const std::string &categoryName);
    std::vector<Book *> getListOfBooksByAuthor(const std::string &author);

    void print();

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    BinarySearchTree<Category> categories;
};


#endif //BOOKCATALOG_H
