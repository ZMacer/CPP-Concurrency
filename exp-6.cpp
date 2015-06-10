#include <iostream>
#include <thread>

int main()
{
    std::thread t([] (){
                std::cout << "thread function\n";
            });
    std::cout << "main function\n";
    t.join();
    return 0;

}
