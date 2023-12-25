#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>
#include "E:\program\code\keshe\my_map.h"

#define ll long long

using namespace std;

//map、第一版本，和std::map基本一致，但是修复了几个问题。
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    my_map::map<string,int> mp,mp_copy,mp_copy_copy;

    mp.begin();
    mp.end();
    mp["123"]=123;
    mp.clear();
    mp.count("123");
    mp.empty();
    mp.equal_range("123");
    mp.lower_bound("123");
    mp.erase("123");
    mp.insert({"123",123});
    mp.find("123");
    mp.max_size();
    mp.size();
    mp.swap(mp_copy);
    mp.upper_bound("123");
    mp=mp_copy;
    mp==mp_copy;
    mp!=mp_copy;
    
    cout<<endl;
    system("pause");
    return 0;
}
