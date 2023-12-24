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

    void reverse(int l,int r,string &s)
    {
        while(l<r)
            swap(s[l++],s[r--]);
    }

    string reverseWords(string s) {
       int n=s.size(),l=0,r=0;

        while(r<n&&s[r]==' ')++r;

        //代码化简前
        // while(r<n)
        // {
        //     if(s[r]!=' ')s[l++]=s[r++];
        //     else 
        //     {
        //         if(r<n-1&&s[r]==s[r+1])
        //             ++r;
        //         else if(r!=n-1)
        //             s[l++]=s[r++];
        //         else 
        //             ++r;
        //     }
        // }

        //代码化简后
        while(r<n)
        {
            //如果s[r]不是空格，直接复制过去。
            //如果是空格，首先判断r是不是n-1，如果是n-1就不复制过去了，不然会过去一个空格
            //如果不是n-1，同时不是两个连续的空格，那么就可以复制过去
            //利用了短路原理
            if(s[r]!=' '||(r!=n-1&&s[r]!=s[r+1]))s[l++]=s[r];
            ++r;
        }

        s.erase(s.begin()+l,s.end());
        reverse(0,l-1,s);


        r=0,l=0,n=s.size();

        while(r<n)
        {
            if(s[r]!=' ')++r;
            else
            {
                reverse(l,r-1,s);
                l=++r;
            }
        }

        reverse(l,r-1,s);

        return s;
    }
};

int main()
{
  //  ios::sync_with_stdio(false);
  //  cin.tie(0),cout.tie(0);

    int t ;
    cin>>t;

    while(t--)
    {
        Solution one;
        string s;

        getline(cin,s);

        cout<<one.reverseWords(s)<<endl;
    }


    cout<<endl;
    system("pause");
    return 0;
}
