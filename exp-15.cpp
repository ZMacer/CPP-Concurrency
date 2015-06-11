#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <cassert>

int main(){
    std::vector<std::thread> workers;
    for ( int i =0; i<5; i++ )
    {
        auto t = std::thread([i]()
                {
                    std::cout << "thread function: " << i << "\n";
                });
        workers.push_back(std::move(t));
    }
    std::cout << "main thread\n";
    std::for_each(workers.begin(),workers.end(),[](std::thread &t)
            {
                assert(t.joinable());
                t.join();
            });
    return 0;
}
