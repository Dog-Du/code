#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//const只能在初始化的时候进行赋值，其他时候都不能赋值
struct node{
    const int a;

    node():a(1){cout<<a<<endl;}
    node(int x):a(x){cout<<a<<endl;}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    node a,b(10);

    const int & x=1;//这样是合理的。
//因为编译器会将这个常量值（1）转换为一个临时的匿名变量，然后将其绑定到一个常量引用 x 上。

// 这里的 const int &x 是一个常量引用，它可以绑定到一个常量或者一个可以转换为常量的临时值。1 是一个常量值，而且可以转换为一个临时的 const int 类型，所以可以将这个常量值赋给一个常量引用 x。

// 常量引用的作用在于允许我们使用常量值，同时避免了拷贝数据。这种方式在函数参数传递时很有用，可以避免不必要的数据拷贝，提高效率.

    cout<<endl;
    system("pause");
    return 0;
}
