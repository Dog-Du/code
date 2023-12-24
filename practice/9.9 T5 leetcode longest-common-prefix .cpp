#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:

    static const int maxn=200*200;

    int t[maxn<<2][26][2]={0},cnt=1;

    void build(string &s)
    {
        int p=0;

        for(auto&it:s)
        {
            if(!t[p][it-'a'][0])
                t[p][it-'a'][0]=cnt++;
            
            ++t[p][it-'a'][1];
            p=t[p][it-'a'][0];
        }
    }

    string longestCommonPrefix(vector<string>& strs) {
        int ans=0,n=strs.size(),p=0;

        for(auto&it:strs)
            build(it);
        
        while(1)
        {
            bool flag=0;

            for(int i=0;i<26;++i)
                if(t[p][i][1]&&t[p][i][1]==n)
                {
                    ++ans;
                    p=t[p][i][0];
                    flag=1;
                    break;
                }
            
            if(!flag)return strs.front().substr(0,ans);
        }

        return "";
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<string> vec;
    vec.push_back("a");

    cout<<one.longestCommonPrefix(vec);


    cout<<endl;
    system("pause");
    return 0;
}
