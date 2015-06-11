#include <iostream>
#include <string>
using namespace std;
class A
{
public:
    A():s("default"){ cout << "默认构造函数A\n"; }
    A(const A& o):s(o.s) { cout <<"复制构造函数A - move failed\n"; }
    A(A&& o): s(move(o.s)) { cout << "移动构造函数A(a&&)\n"; }
    string printObj() { return s; }
private:
    string s;

};
A temp(A a)
{
    return a;
}
class B: public A
{};
class C: public B
{
public:
    ~C() {};
};

int main()
{
    // calls default constructor
  C b1;

    // calls implicit move constructor
    C b2 = std::move(b1);

    return 0;
}
