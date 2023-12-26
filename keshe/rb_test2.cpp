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
//B类第九题红黑平衡二叉树及其应用

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    my_map::map<string,int> mp,mp_copy,mp_copy_copy;
    string str[10];

    //std::map
    map<string,int> std_mp;
    auto std_iter=std_mp.begin();
    //std_iter._M_node; //std的迭代器 中指针暴露出来了。
    
    //++std_iter; //空树时，std的迭代器++会无限循环--会报错
    //--std_iter;
    
    auto my_iter=mp.begin();
    //my_iter.M_node; //报错，因为protected,通过友元避免了M_node漏出
    ++my_iter;
    --my_iter;

    for(int i=0;i<10;++i)
    {
        string s;
        s.push_back('a'+i);
        s=s+s+s;
        str[i]=s;

        //插入时返回一个pair，第一个元素是迭代器，第二个元素是是否插入成功。
        //重载了[]符号，所以也可以使用[]进行插入或者查询
        //mp[str[i]]=i;
        //my_map::map<string,int>::iterator iter=mp.find(s);

       pair<my_map::map<string,int>::iterator,bool> iter_pair=mp.insert({str[i],i});
        cout<<str[i]<<endl;
        my_map::map<string,int>::iterator iter=iter_pair.first;
        //cout<< (iter_pair.second?"success":"fail") <<endl;
        //cout<< iter->first << ' ' << iter->second <<endl;
    }

    // cout<<endl;
    // cout<<"for():"<<endl;


    // for(auto&it:mp)//因为迭代器中有 begin() end() != ++ * 所以支持范围for循环
    // {
    //     cout<<it.first<<' '<<it.second<<endl;
    // }

    cout<<"\nerase(iterator):"<<endl;

    mp_copy=mp;//深拷贝

    for(my_map::map<string,int>::iterator iter=mp.begin();iter!=mp.end();)
    {
        cout<<iter->first<<' '<<iter->second<<endl;
        iter=mp.erase(iter);//删除的时候会返回下一个迭代器，所以可以通过这种方式进行迭代。
    }

    // for(auto&it:mp)//mp已经被删除
    // {
    //     cout<<it.first<<' '<<it.second<<endl;
    // }

    // cout<<"\nmp_copy"<<endl;
    // for(auto&it:mp_copy)
    // {
    //     cout<<it.first<<' '<<it.second<<endl;
    // }

    cout<<"\nerase(value) and find(value)"<<endl;

    mp_copy_copy=mp_copy;

    for(int i=0;i<10;++i)
    {
        my_map::map<string,int>::iterator iter=mp_copy.find(str[i]);
        cout<<iter->first<<' '<<iter->second<<endl;
        cout<< "erase number : "<< mp_copy.erase(str[i]) <<endl;
    }

    for(int i=0;i<26;++i)//通过迭代器查找
    {
        string s;
        s.push_back('a'+i);
        s=s+s+s;
        my_map::map<string,int>::iterator iter=mp_copy_copy.find(s);
        cout<< (iter==mp_copy_copy.end()?"fail ":"success ") << 
            (iter==mp_copy_copy.end()?string(""):iter->first)<<endl;
    }

    
    cout<<endl;
    system("pause");
    return 0;
}
