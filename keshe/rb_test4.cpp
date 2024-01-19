#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>
#include "E:\program\code\keshe\my_mapv2.0.h"

#define ll long long

using namespace std;

//map展示所有函数，同时编译无误
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    my_map::map<string,int> mp,mp_copy,mp_copy_copy;

    mp.insert({"abckasd",123});
    cout<< mp.begin()->first << mp.begin()->second<<endl;

//     mp.begin();
//     mp.end();

//     mp.count("123");
//     mp.empty();

//     //马天野 : 查找功能。
//     mp.equal_range("123");
//     mp.lower_bound("123");
//     mp.upper_bound("123");
//     mp.find("123");
//     mp.swap(mp_copy);
//    //mp.get_rank("123");
//    // mp.get_val(123);
//     mp["123"]=123;

//     //马润豪 : 删除
//     mp.erase("123");
//     mp.erase(mp.begin(),mp.end());
//     mp.erase(mp.begin());
//     mp.clear();

//     mp.max_size();
//     mp.size();

//     mp.insert({"123",123});
//     mp.insert(mp.begin(),{"123",123});
//     mp.insert(mp.end(),{"111",111});
//     mp.insert(mp.begin(),{"321",312});
    
//     for(auto&it:mp)
//     {
//         cout<<it.first<<' '<<it.second<<endl;
//     }

//     mp=mp_copy;
//     mp==mp_copy;
//     mp!=mp_copy;
    
//     auto it=mp.begin();
    
    cout<<endl;
    system("pause");
    return 0;
}
