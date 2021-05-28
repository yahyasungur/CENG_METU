#include <iostream>

#include "BookCatalog.h"

int main() {
    std::cout << "-> Creating a book catalog with default constructor." << std::endl;

    BookCatalog catalog;

    std::cout << "-> Making some category insertions to the catalog." << std::endl;
    catalog.addCategory("history");
    catalog.addCategory("computer science");
    catalog.addCategory("sci-fi & fantasy");
    catalog.addCategory("parenting");
    
    std::cout << "-> Printing the catalog." << std::endl;

    //catalog.print();

    std::cout << "-> Making some book insertions to the catalog." << std::endl;

    catalog.addBook("computer science", Book("978-0132847377", "Data Structures and Algorithm Analysis in C++", "Mark Allen Weiss"));
    catalog.addBook("computer science", Book("978-0262533058", "Introduction to Algorithms", "Thomas H. Cormen"));
    catalog.addBook("computer science", Book("978-0132624787", "Elements of the Theory of Computation", "Harry R. Lewis"));

    catalog.addBook("parenting", Book("978-1328974860", "How to Raise Successful People", "Esther Wojcicki"));
    catalog.addBook("parenting", Book("978-0609809884", "Between Parent and Child", "Haim G. Ginott"));

    catalog.addBook("sci-fi & fantasy", Book("978-0553103540", "A Game of Thrones", "George R. R. Martin"));
    catalog.addBook("sci-fi & fantasy", Book("978-0553108033", "A Clash of Kings", "George R. R. Martin"));
    catalog.addBook("sci-fi & fantasy", Book("978-0553106633", "A Storm of Swords", "George R. R. Martin"));
    catalog.addBook("sci-fi & fantasy", Book("978-0553801507", "A Feast for Crows", "George R. R. Martin"));
    catalog.addBook("sci-fi & fantasy", Book("978-0553801477", "A Dance with Dragons", "George R. R. Martin"));

    catalog.addBook("sci-fi & fantasy", Book("978-0547928241", "The Hobbit", "J. R. R. Tolkien"));
    catalog.addBook("sci-fi & fantasy", Book("978-0395489314", "The Lord of the Rings: The Fellowship of the Ring", "J. R. R. Tolkien"));
    catalog.addBook("sci-fi & fantasy", Book("978-0395489338", "The Lord of the Rings: The Two Towers", "J. R. R. Tolkien"));
    catalog.addBook("sci-fi & fantasy", Book("978-0395489307", "The Lord of the Rings: The Return of the King", "J. R. R. Tolkien"));

    std::cout << "-> Printing the catalog." << std::endl;

    catalog.print();
    

/*     catalog.removeBookByIsbn("978-0132847377");
    catalog.removeBookByIsbn("978-0262533058");
    catalog.removeBookByIsbn("978-0395489307");
    catalog.removeBookByIsbn("978-0547928241");
    catalog.removeBookByIsbn("978-0553106633"); */


/*     std::cout << "-> ------------------------isbn--------------------" << std::endl;

    catalog.print(); */

    //catalog.removeBookByTitle("Between Parent and Child");
    catalog.removeBookByTitle("The Lord of the Rings: The Two Towers");
/*  catalog.removeBookByTitle("A Clash of Kings");
    catalog.removeBookByTitle("A Dance with Dragons"); */

    //std::cout << "-> -------------------title-------------------------" << std::endl;

    catalog.print();

/*     Book *b = catalog.searchBookByTitle("A Storm of Swords");

    std::cout << (*b) << std::endl; */
    return 0;
}
