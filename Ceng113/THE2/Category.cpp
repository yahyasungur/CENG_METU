#include "Category.h"

Category::Category() {

}

Category::Category(const std::string &name) {

    this->name = name;
}

const std::string &Category::getName() const {

    return this->name;
}

void Category::addBook(const Book &book) {
    this->books.insert(book);
}

void Category::removeBook(const Book &book) {
    this->books.remove(book);
}

Book *Category::searchBook(const Book &book) {
    Node<Book> * temp = this->books.findWithoutOrderingProperty(book);
    if (temp){
        return (&(temp->element));
    }
    return NULL;
}

std::vector<Book *> Category::getListOfBooks() {
    std::vector<Book *> b;
    std::vector<Node<Book>*> n = this->books.getListOfAllNodes();
    int size = n.size();
    for (int i = 0; i < size; i++){
        b.push_back(&(n[i]->element));
    }
    return b;
}

bool Category::operator<(const Category &rhs) const {

    // compare category names.
    return this->name < rhs.name;
}

bool Category::operator>(const Category &rhs) const {

    // compare category names.
    return this->name > rhs.name;
}

bool Category::operator==(const Category &rhs) const {

    // compare category names for equality.
    return this->name == rhs.name;
}

std::ostream &operator<<(std::ostream &os, const Category &category) {

    os << "Category(name: " << category.name << ", books: " << category.books << ")";
    return os;
}
