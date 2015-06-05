#include <iostream>
#include <thread>

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
    int some_local_state=0;
    func my_func(some_local_state);
    std::thead t(my_func);
    try
    {
        do_some_in_current_thread();

    }
    catch(...)
    {
        t.join();
        throw;
    }//方法一: 使用try --catch 确保在意外退出时仍然正确调用t.join等待函数
    t.join();
}

class thread_guard
{
    std::thread& t;
    public:
        explicit thread_guard(std::thread& t_):t(t_){}
        ~thread_guard()
        {
            if(t.joinable())
            {
                t.join();
            }
        }
        thread_guard(thread_guard const &) = delete;//禁止默认复制构造函数
        thread_guard& operator=(thread_guard const&) = delete;//禁止默认赋值构造函数
} //RAII
struct func;
 void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);//方法二：确保当前线程退出时，正确等待线程t完成
    do_something_in_current_thread();
}
//-----------------------------------------------------------------------------------------------
//example for detach
void edit_document(std::string const& filename)
{
    open_document_and_display_gui(filename);
    while(!done_editing())
    {
        user_command cmd= get_user_input();
        if(cmd.type == open_new_document)
        {
            std::string const new_name = get_filename_from_user();
            std::thread t(edit_docment,new_name);
            t.detach();
        }
        else
        {
            process_user_input(cmd);
        }
    }
}
