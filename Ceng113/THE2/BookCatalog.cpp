#include "BookCatalog.h"

// PUBLIC MEMBER FUNCTIONS.

BookCatalog::BookCatalog() {

}

const BinarySearchTree<Category> &BookCatalog::getCategories() const {

    return this->categories;
}

void BookCatalog::addCategory(const std::string &categoryName) {
    this->categories.insert(Category(categoryName));
}

void BookCatalog::removeCategory(const std::string &categoryName) {
    this->categories.remove(Category(categoryName));
}

Category *BookCatalog::searchCategory(const std::string &categoryName) {
    return &(this->categories.find(Category(categoryName))->element);
}

void BookCatalog::addBook(const std::string &categoryName, const Book &book) {
    Category * temp = this->searchCategory(categoryName);
    if (temp == NULL){
        this->addCategory(categoryName);
        temp = this->searchCategory(categoryName);
    }
    temp->addBook(book);
}

void BookCatalog::removeBookByIsbn(const std::string &isbn) {
    Node<Category> * root = this->categories.getRoot();

    if (root == NULL) {
        return;
    }
    std::queue<Node<Category>*> q;
    q.push(root);

    while (q.empty() == false){
        Node<Category>* node = q.front();
        node->element.removeBook(Book(isbn,"\0","\0"));
        q.pop();

        if (node->left){
            q.push(node->left);
        }
        if (node->right){
            q.push(node->right);
        }
    }
}

void BookCatalog::removeBookByTitle(const std::string &title) {
    Node<Category> * root = this->categories.getRoot();

    if (root == NULL) {
        return;
    }
    std::queue<Node<Category>*> q;
    q.push(root);

    while (q.empty() == false){
        Node<Category>* node = q.front();
        if (node->element.searchBook(Book("\0",title,"\0"))){
            node->element.removeBook(Book("\0",title,"\0"));
        }
        q.pop();

        if (node->left){
            q.push(node->left);
        }
        if (node->right){
            q.push(node->right);
        }
    }
}

Book *BookCatalog::searchBookByIsbn(const std::string &isbn) {
    Node<Category> * root = this->categories.getRoot();

    if (root == NULL) {
        return NULL;
    }
    std::queue<Node<Category>*> q;
    q.push(root);

    while (q.empty() == false){
        Node<Category>* node = q.front();
        if(node->element.searchBook(Book(isbn,"\0","\0"))){
            return node->element.searchBook(Book(isbn,"\0","\0"));
        }
        q.pop();

        if (node->left){
            q.push(node->left);
        }
        if (node->right){
            q.push(node->right);
        }
    }
    return NULL;
}

Book *BookCatalog::searchBookByTitle(const std::string &title) {
    Node<Category> * root = this->categories.getRoot();

    if (root == NULL) {
        return NULL;
    }
    std::queue<Node<Category>*> q;
    q.push(root);

    while (q.empty() == false){
        Node<Category>* node = q.front();
        if(node->element.searchBook(Book("\0",title,"\0"))){
            return node->element.searchBook(Book("\0",title,"\0"));
        }
        q.pop();

        if (node->left){
            q.push(node->left);
        }
        if (node->right){
            q.push(node->right);
        }
    }
    return NULL;
}

std::vector<Book *> BookCatalog::getListOfBooksByCategory(const std::string &categoryName) {
    return this->searchCategory(categoryName)->getListOfBooks();
}

std::vector<Book *> BookCatalog::getListOfBooksByAuthor(const std::string &author) {
    std::vector<Book *> x;
    std::vector<Book *> y;
    std::vector<Book *> all;
    Node<Category> * root = this->categories.getRoot();

    if(root == NULL){
        return x;
    }
    std::queue<Node<Category>*> q;
    q.push(root);

    while (q.empty() == false){
        Node<Category>* node = q.front();
        x = node->element.getListOfBooks();
        all.insert(all.begin(),x.begin(),x.end());
        all.insert(all.end(),y.begin(),y.end());
        q.pop();

        if (node->left){
            q.push(node->left);
        }
        if (node->right){
            q.push(node->right);
        }
    }
    y.clear();
    x.clear();


    for (int i = 0; i < all.size(); i++){
        if (all[i]->getAuthor() == author){
            y.push_back(all[i]);
        }
    }
    std::string min;
    int index;

    for (int i = 0; i < y.size(); i++){
        min = "999-9999999999";
        index = 0;
        for (int j = 0; j < y.size(); j++){
            if (y[j] != NULL && y[j]->getIsbn() < min){
                min = y[j]->getIsbn();
                index = j;
            }
        }
        x.push_back(y[index]);
        y[index] = NULL;
    }
    return x;
}

void BookCatalog::print() {

    // printing the binary search tree of categories.
    std::cout << "<BookCatalog>\n" << categories << "\n</BookCatalog>" << std::endl;
}
