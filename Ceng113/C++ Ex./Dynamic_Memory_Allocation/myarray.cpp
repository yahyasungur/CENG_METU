#include "myarray.h"


//Set size to two and n to zero and set arr to point an array of two integers.
MyArray::MyArray()
{
    this->size = 2;
    this->n = 0;
    this->arr = new int[2];
    // TODO 
}

//Set size to two and n to one and set array to point an array of two integers
//The first element in the array must be first_el
MyArray::MyArray(int first_el)
{
    this->size = 2;
    this->n = 1;
    this->arr = new int[2];
    arr[0] = first_el;
    // TODO
}

// Set size and n of the newly created MyArray same as  the size and n of rhs 
// Allocate new space and assign it to arr of the newly created MyArray
// Copy all elements in rhs to arr of the newly created MyArray
MyArray::MyArray(const MyArray& rhs)
{   
    this->size = rhs.size;
    this->n = rhs.n;
    this->arr = new int[size];
    for (int i = 0; i < size; i++){
        this->arr[i] = rhs.arr[i];
    }
    // TODO
}

// Set size and n to zero and deallocate arr.
MyArray::~MyArray()
{
    this->size = 0;
    this->n = 0;
    delete [] arr;
}

// Similar to copy constructor (i.e. deep copy semantics)
// Make sure you don't assign object to itself.
MyArray& MyArray::operator=(const MyArray& rhs)
{
    this->size = rhs.size;
    this->n = rhs.n;
    delete [] this->arr;
    this->arr = new int[size];
    for (int i = 0; i < n; i++){
        this->arr[i] = rhs.arr[i];
    }
    return *this;
    // TODO
}


// Allocate a bigger array of size (2*size).
// Copy n elements in arr to the new space.
// At the end of the function execution, arr must point to the bigger array 
// Set size correctly.
// Don't forget to delete the old space.
void MyArray::double_size()
{   
    int *a = new int[size*2];
    int *temp = NULL;
    for (int i = 0; i < size; i++){
        a[i] = this->arr[i];
    }
    temp = this->arr;
    this->arr = a;
    delete [] temp;
    size = size*2;
    // TODO
}

// Check if arr is full
// If it is full double the size of arr (i.e. call double_size function)
// Insert element as the last item in the arr.
// Don't forget to increment n.
void MyArray::insert_data(int el)
{   
    if (n == size){
        double_size();
    }
    this->arr[n] = el;
    n++;
    // TODO
}

// You can assume that ind >=0 and ind < n.
// Delete the element at ind, by shifting all elements after index ind
// one position to the left.
// You don't change the size but you must decrement n.
void MyArray::delete_data(int ind)
{
    for (int i = ind; i < n; i++){
        this->arr[i] = this->arr[i+1];
    }
    n--;
    // TODO
}

int MyArray::get_n()
{
    return n;
}

int MyArray::get_size()
{
    return size;
}

// gets the element in ind index where 0 <= ind < n. 
int MyArray::get_element(int ind)
{
    return arr[ind];
}

// Note that default parameters are only
// specified in the function declaration
// (not the definition, which is below).
void MyArray::print(char separator) const
{
    for (int i = 0; i < n-1; i++)
    {
        // We should use braces in "for", "if", "while"
        // constructs even if we have a single line
        // of code. This improves code clarity.
        
        std::cout << arr[i] << separator;
    }
    
    std::cout << arr[n-1] << std::endl;
}


