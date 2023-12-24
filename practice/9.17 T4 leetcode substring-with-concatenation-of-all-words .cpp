#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define ll long long

using namespace std;


//字符串形式的滑动窗口罢了
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        int n=words.size(),length=words.front().size(),m=s.size();
        if(m<n*length)return ans;
        unordered_map<string,int> pre,mp;

        for(auto&it:words)pre[it]++;

        //对刚开始的几种起始进行循环 类似于 x%3 会有 0 1 2 三种情况
        for(int i=0;i<length;++i)
        {
            mp=pre;//mp复原
            
            //滑动窗口
            for(int l=i,r=i;r+length-1<m;r+=length)
            {
                string temp=s.substr(r,length);

                if(!mp.count(temp))//如果没有这个字符段，那么下次必须从r+length那个地方开始匹配，所以这个循环是回收的
                {
                    //全部回收
                    while(l<r)
                    {
                        mp[s.substr(l,length)]++;
                        l+=length;
                    }
                    l+=length;
                }
                else if(mp[temp]==0)//用完了和匹配失败类似，需要回收，但是下次匹配是从r开始的，不是从r+length开始的，所以需要r-=length
                {
                    //一部分回收
                     while(s.substr(l,length)!=temp)
                    {
                        mp[s.substr(l,length)]++;
                        l+=length;
                    }

                    mp[s.substr(l,length)]++;
                    l+=length;
                    r-=length;
                }
                else//匹配成功
                {
                    mp[temp]--;

                    //如果长度到位了，说明全部匹配成功，把l+length并且回收，开始下一次匹配
                    if(r-l==n*length-length)
                    {
                        ans.push_back(l);
                        mp[s.substr(l,length)]++;
                        l+=length;
                    }
                }  

                
            }
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    string s="barfoothefoobarman";
    vector<string> vec={"foo","bar"};
    one.findSubstring(s,vec);

    cout<<endl;
    system("pause");
    return 0;
}
