#include <iostream>
#include <string>

using namespace std;
class A
{
public:
    // default constructor
    A() : s("default") { cout << "default constructor A\n"; }

    // copy constructor
    A(const A& o) : s(o.s) { cout << "copy constructor A - move failed!\n";}

    // move constructor
    A(A&& o) : s(move(o.s)) { cout << "move constructor A(A&&) called\n"; }

    string printObj() { return s; }
private:
    string s;
};

A temp(A a) {
    return a;
}

class B : public A
{};

class C : public B
{
public:
    //  this destructor prevents implicit move ctor C::(C&&)
    //~C() {};
};

class D : public A
{
public:
    //  default constructor
    D() {}

    // destructor would prevent implicit move constructor D::(D&&)
    ~D() {};

    // forced use of move constructor
    D(D&&) = default;
};

int main()
{
    D d1; 
    D d2 = std::move(d1);

    return 0;
}
