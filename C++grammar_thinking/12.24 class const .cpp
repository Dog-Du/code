#include <iostream>

//const 类型只能调用const修饰的成员对象
//const函数中也只能调用const修饰的函数
//这一点在operator函数中也是一样的。
//需要注意，一个函数的参数可能会因为const而导致无法传参。
//比如:operator==(const class& x)const 应该写成这样，避免无法传参
//因为里层的也会写const，红黑树课设选择了这种写法，但是一般推荐使用的是全局方法似乎。

class myint{
public:
    int a;
    myint():a(1){}

    void print()const
    {
        std::cout<<a<<std::endl;
    }

    const int& get()const
    {
        set(10);
        return a;
    }

    void set(int x)
    {
        a=x;
    }
};
int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0),std::cin.tie(0);

    const myint a;
    a.a=10;


	std::cout<<std::endl;
	system("pause");
	return 0;
}