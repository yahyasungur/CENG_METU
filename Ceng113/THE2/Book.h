#ifndef BOOK_H
#define BOOK_H


// DO NOT CHANGE THIS FILE.

#include <iostream>

class Book {
public:
    Book();
    Book(const std::string &isbn, const std::string &title, const std::string &author);

    const std::string &getIsbn() const;
    const std::string &getTitle() const;
    const std::string &getAuthor() const;

    bool operator<(const Book &rhs) const;
    bool operator>(const Book &rhs) const;
    bool operator==(const Book &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Book &book);

private:
    std::string isbn;
    std::string title;
    std::string author;
};


#endif //BOOK_H
