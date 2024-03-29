#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include "E:\program\code\keshe\my_mapv2.0.h"

#define ll long long

using namespace std;

//my_mapv2.0在节点底层增加了node_count属性，实现了logn时间的获取排名和log时间通过排名查找值
//值x的rank（排名）的定义是：小于比x小的值的个数 + 1

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    my_map::map<unsigned ll,int> mp;

    for(unsigned ll i=0;i<=10;++i)
    {
        mp.insert({i,10-i});
    }

    cout<<"get_rank()"<<endl;
    for(unsigned ll i=0;i<=10;++i)
    {
        cout<<mp.get_rank(i)<<endl;
    }

    cout<<"get_val()"<<endl;
    for(unsigned ll i=0;i<=10;++i)
    {
        cout<<mp.get_val(i)->first<<endl;//get_val函数输入排名，返回对应排名的迭代器。
    }

    cout<<endl;
    system("pause");
    return 0;
}
