#include <iostream>
#include <thread>

void f(int i, std:string const& s);
//此函数会造成变量未定义错误，因为在buffer重char * 转变为std:string 过程中就有可能已经销毁
//
void oops(int some_param)
{
    char buffer[1024];
    sprintf(buffer, "%i",some_param);
    std::thread t(f,3,buffer);
    t.detach
}

void not_oops(int some_param)
{
    char buffer[1024];
    sprintf(buffer,"%i",some_param);
    std::thread t(f,3,std:string(buffer));//先显示转化过后再传入
    t.detach();

}
//====================================================================

void updata_data_for_widget(wedget_id w,widget_data& data);
void oops_again(widget_id w)
{
    widget_data data;
    std::thread t(updata_data_for_widget,w,data);//oops
    std::thread t(updata_data_for_widget,w,std::ref(data));//not oops
    display_status();
    t.join();
    process_widget_data(data);
}
//===================================================================

class X 
{
public:
    void do_lengthy_work();

};

X my_x;
std::thread t(&X::do_length_work,&my_x);
//function my_x.do_length_work run on a new thread
//===================================================================
std::thread f()
{
    void some_function();
    return std::thread(some_function);
}
std:: thread g()
{
    void some_other_function(int);
    std::thread t(some_other_function,42);
    retun t;
}
//===========================================================
//
void f(std::thread t);
void g()
{
    void some_function();
    f(std::thread(some_function));
    std::thread t(some_function);
    f(std::move(t));
}

class scoped_thread
{
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):
        t(std::move(t_))
    {
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(scoped_thread const&) =delete;
    scoped_thread& operator=(scoped_thread const& ) =delete;

};
struct func
{
    int& i;
    func(int& i_):i(i_){}

    void operator() ()
    {
        for(unsigned j=0; j<1000000; ++j)
        {
            do_something(i);
        }
    }
}

struct func;
void f()
{
    int some_local_state;
    scoped_thread t(std::thread(func(some_localstate)));
    do_something_in_current_thread();
}
//================================================
void do_work(unsigned id);
void f()
{
    std::vector<std::thread> threads;
    for (unsigned i = 0;i<20;++i)
    {
        threads.push_back(std::thread(do_work,i));
    }
    std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));
}
//==============================================================
template<typenamw Iterator, typename T>
struct accumulate_block
{
    void operator() (Iterator first, Iterator last, T& result)
    {
        return std::accumulate(first,last,result);
    }
}

template<typename Iterator,typename T>
T parallel_accumlate(Iterator first,Iterator last,T init)
{
    unsigned long const length= std::distance(first,last);
    if(!length)
        return init;
    unsigned long const min_per_thread=25;
    unsigned long const max_threads= 
        (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads=
        std::thread::hardware_concurrency();
    unsigned long const num_threads = 
        std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size=length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);
    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        threads[i] = std::thread(
                accumulate_block<Iterator,T>(),
                block_start,block_end,std::ref(results[i]));
        block_start = block_end;

    }
    accumulate_block<Iterator,T>()(
            block_start,last,results[num_threads -1]);
    std::for_each(threads.begin(),threads.end(),
            std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(),results.end(),init);
}
std::thread::id master_thread;
void some_core_part_of_algorithm()
{
    if(std::this_thread::get_id()==master_thread)
    {
        do_master_thread_work();
    }
    do_common_work();
}
