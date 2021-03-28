#include<iostream>

using namespace std;

class Complex
{
private:
    float re,im;
public:
    Complex();
    ~Complex();

    Complex operator* (Complex rhs) const{
        Complex prod;
        prod.re = re*rhs.re - im*rhs.im;
        prod.im = re*rhs.im - im*rhs.re;
        return prod;
    }
    Complex operator* (float k) const {
        Complex prod;
        prod.re = re*k;
        prod.im = im*k;
        return prod;
    }

    friend Complex operator* (float k, Complex rhs);

    void assign(float newre,float newim){
        re = newre;
        im = newim;
    }

    void print() const{
        cout << "re: " << re << " im: " << im << endl;
    }
};

Complex::Complex()
{
    re = 0;
    im = 0;
}

Complex::~Complex()
{
}

Complex operator*(float k, Complex rhs){
    Complex prod;
    prod.re = rhs.re * k;
    prod.im = k* rhs.im;
    return prod;    
}



int main(){
    int k = 1;
    Complex c1,c2,c3;
    c3.print();
    c3 = c3*k;
    c3.print();
    c3.assign(1.2,1.2);
    c3 = c3*k;
    c3.print();
    c1.assign(14,2.1);
    c3 = c3*c1;
    c3.print();
    c3 = k*c1;
    c3.print();

    return 0;
}