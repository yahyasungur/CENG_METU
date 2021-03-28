#include "myarray.h"

using namespace std;

int main()
{
    MyArray arr_obj;
    arr_obj.print();
    MyArray obj1(12);
    obj1.print();
    MyArray obj2(obj1);
    obj2.print();
    
    // You can test your implementation here.
    

    return 0;
}
