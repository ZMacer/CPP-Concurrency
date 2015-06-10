#include <iostream>
#include <vector>

class A
{
public:
    int mx;
    double my;

};

class B
{
public:
    B(int x,double y):mx{ x }, my{ y } { }

    int mx;
    double my;
};

class C
{
public:
    C(int x, double y):mx{ x },my{ y } { }
    C(const std::initializer_list<int> & v) {
            mx = *(v.begin());
            my = *(v.begin() + 1);
    }
    int mx;
    double my;
};

int main()
{
    A a{ 1, 3.7 };
    B b{ 2, 9.8 };
    C c{ 3, 7 };
    std::cout << a.mx << " " << a.my << std::endl;
    std::cout << b.mx << " " << b.my << std::endl;
    std::cout << c.mx << " " << c.my << std::endl;
    return 0;
}
