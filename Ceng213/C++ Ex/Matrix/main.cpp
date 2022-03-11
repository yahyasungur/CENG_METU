#include <iostream>
#include "matrix.hpp"

int main()
{
    // You can test your implementation here.
    Matrix m1(5);
    Matrix m2(5);
    Matrix m3(5);

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++)
        {
            m1.set_number(i,j,i);
        }
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++)
        {
            m2.set_number(i,j,i+j);
        }
    }

    std::cout << m1 << std:: endl;
    std::cout << m2 << std:: endl;

    m3 = m2;

    std::cout << m3 << std:: endl;

    m3.sum_with(m2);

    std::cout << m3 << std:: endl;

    m3.substract(m1);

    std::cout << m3 << std:: endl;

    return 0;
}
