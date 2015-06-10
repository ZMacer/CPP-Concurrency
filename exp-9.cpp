#include <iostream>
#include <algorithm>

class A
{
    public:
       explicit A(size_t length)//初始化构造函数
          :mLength(length),mData(new int[length])
       {
            std::cout << "A(size_t).length = " <<mLength << "." << std::endl;
       }
       ~A()
       {
            std::cout <<"~A().length = " << mLength <<".";
            if (mData != NULL) {
                std::cout << " Deleteing resource.";
                delete[] mData;
            }
            std::cout << std::endl;
       }
       //复制构造函数
       A(const A& other)
           :mLength(other.mLength),mData(new int[other.mLength])
       {
           std::cout << "A(const A&).length = " << other.mLength << ". Copying resource." << std::endl;
           std::copy(other.mData, other.mData + mLength, mData);
       }
       //拷贝赋值运算符
       A& operator=(const A& other)
       {
           std::cout << "operator=(const A&). length = "
	         << other.mLength << ". Copying resource." << std::endl;

           if (this != &other) {
	            delete[] mData;  // Free the existing resource.
	            mLength = other.mLength;
                mData = new int[mLength];
                std::copy(other.mData, other.mData + mLength, mData);
           }
           return *this;
       }
       //移动构造函数
       A(A&& other) : mData(NULL), mLength(0)
      {
        std::cout << "A(A&&).length = " << other.mLength << ". Moving resource.\n";
        mData = other.mData;
        mLength = other.mLength;
        other.mData = NULL;
        other.mLength = 0;
      }
       //移动赋值运算符
      A& operator=(A&& other)
      {
        std:: cout << "operter=(A&&).length = "　<< other.mLength << "." << std::endl;
        if (this != other) {
            delete[] mData;
            mData = other.mData;
            mLength = other.mLength;
            other.mData = NULL;
            other.mLength = 0;
        }
        return *this;
      }
      size_t Length() const
      {
          return mLength;
      }
    private:
      size_t mLength;//数据长度
      int* mData; // 数据指针
};

 int main()
{
    std::vector<A> v;
    v.push_back(A(25));
    v.push_back(A(75));
    v.insert(v.begin() + 1,A(50));
    return 0;
}
