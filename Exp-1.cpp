#include <iostream>
#include <thread>

void sayHello()
{
   std::cout << "Hello world" << std::endl;
}
int main()
{
   std::thread my_thead(sayHello);
   t.join();

}