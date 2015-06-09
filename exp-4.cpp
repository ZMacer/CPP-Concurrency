#include<iostream>
#include<thread>
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(),some_list.end(),value_to_find)!= some_list.end();
}

int main()
{

    return 0;
}
//==================================
//Listing 3.2 Accidentally passing out a reference to protected data
class some_data
{
    int a;
    std::string b;
public:
    void do_something();
};

class data_wrapper
{
    private:
        some_data data;
        std::mutex m;
    public:
        template<typename Function>
        void process_data(Function func)
        {
            std::lock_guard<std::mutex> l(m);
            func(data);

        }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected = &protected_data;
}

data_wrapper x;

void foo()
{
    x.process_data(malicious_function);
    unprotected->do_someting();
}
//================================================================
//=================================================================

template<typename T, typename Container=std::deque<T> >
class stack
{
public:
    explicit stack(const Container&);
    explicit stack(Container&& = Container());
    template <class Alloc> explicit stack(const Alloc&);
    template <class Alloc> stack(const Container&, const Alloc&);
    template <class Alloc> stack(Container&&, const Alloc&);
    template <class Alloc> stack(stack&&,const Alloc&);
    bool empty() const;
    size_t size() const;
    T& top();
    T const& top() const;
    void push(T const&);
    void push(T&&);
    void pop();
    void swap(stack&&);
};

stack<int> s;
if(!s.empty())
{
    int const value=s.top();
    s.pop();
    do_someting(value);
}
