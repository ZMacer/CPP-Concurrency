#include<iostream>

void f(int& i) { std::cout << "lvalue ref: "<< i << "\n"; }
void f(int&& i) { std::cout << "rvalue ref: "<< i << "\n"; }
int main() 
{
    int i = 77;
    f(i);//左值引用
    f(99);//右值引用
    f(std::move(i)); //右值引用
    return 0;
}

// = ==  = = = == == === = == =  == == = = = = == ===== 
#include <iostream>

int getValue()
{
    int ii = 10;
    return ii;
}

int main()
{
    std::cout << getValue();
    //in C++0X
    const int& val = getValue();//ok
    int& val = GetValue();//error
    //in C++11
    const int&& val = getValue(); //ok
    int&& val = getValue();//ok

    return 0;
}

//============================================================
#include <iostream>
using namspace std;
void printReference(int& value)
{
    cout << "lvalue: value = " << value << endl;
}

void printReference(int&& value)
{
    cout << "rvalue: value = " << value << endl;
}

int getValue()
{
    int temp_ii = 99;
    return temp_ii;
}

int main()
{
    int ii = 11;
    printReference(ii);
    printReference(getValue());
    return 0;
}
