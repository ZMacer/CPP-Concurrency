#include <iostream>
using namespace std;

class A 
{
    public:
        explicit A(size_t length)
            :mLength(length), mData(new int[length]){}
        A(A&& other)
        {
            mData  = other.mData;
            mLength =  other.mLength;
            other.mData = nullptr;
            other.mLength = 0;
        }
        A& operator=(A&& other) noexcept
        {
            mData = other.mData;
            mLength = other.mLength;
            other.mData = nullptr;
            other.mLength = 0;
            return *this; 
        }
        
        size_t getLength() { return mLength; }
        
        void swap(A& other)
        {
            A temp = move(other);
            other = move(*this);
            *this = move(temp);
        }
        int* get_mData() { return mData; }
    private:
        int *mData;
        size_t mLength;

}

int main()
{
    A a(11),b(22);
    cout << a.getLength() << ' ' << b.getLength() << endl;
    cout << a.get_mData() << ' ' << b.get_mData() << endl;
    swap(a,b);
    cout << a.getLength() << ' ' << b.getLength() << endl;
    cout << a.get_mData() << ' ' << b.get_mData() << endl;
    return 0;
}
