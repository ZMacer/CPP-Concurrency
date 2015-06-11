#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    A(): s("default")
    {
        cout <<"默认构造函数\n";
    }
    A(const A& o):s(o.s) {
        cout << "复制构造函数A - move fails!\n";
    }
    A(A&& o): s(move(o.s))
    {
        cout << "移动构造函数 A(A&&) called\n";
    }
    string printObj() { return s; }
private:
    string s;
};

A temp(A a) {
    return a;
}

class B: public A
{};

int main()
{
    B b1;
    B b2 = std:: move(b1);
    return 0;
}
