#include <iostream>
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>

using namespace std;

std::list<int>myList;
std::mutex myMutex;

void addToList(int max, int interval)
{
    std::lock_guard<std::mutex> guard(myMutex);
    for (int i = 0; i < max; i++)
    {
        if( (i % interval) == 0 ) myList.push_back(i);
    }

}

void printList()
{
    std::lock_guard<std::mutex> guard(myMutex);
    for ( auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr ) 
    {
        cout << *itr << ",";
    }
}

void printList_for_each()
{
     std::lock_guard<std::mutex> guard(myMutex);
    for_each(myList.begin(),myList.end(),[](int i){
            cout << i <<",";
            }); 
}

int main()
{
	int max = 100;

	std::thread t1(addToList, max, 1);
	std::thread t2(addToList, max, 10);
	//std::thread t3(printList);
	std::thread t3(printList_for_each);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
