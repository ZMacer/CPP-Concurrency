#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

int main()
{
    std:: vector<std::thread> workers;
    for (int i =0; i<5; i++) {
        workers.push_back(std::thread([] ()
                    {
                        std::cout << "thread function\n";
                    }));
    }
    std::cout << "main thread\n";
    std::for_each(workers.begin(), workers.end(),[] (std::thread &t)
            {
                t.join();
            });
    return 0;
}
