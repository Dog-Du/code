#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define ll long long

using namespace std;

class Solution {
public:

    bool check(unordered_map<char,int> &mp)
    {
        for(auto&it:mp)
            if(it.second>0)return false;
        return true;
    }

    string minWindow(string s, string t) {
        int res=0,length=12345678,n=s.size();
        unordered_map<char,int> mp;

        for(auto&it:t)mp[it]++;

        for(int l=0,r=0;r<n;++r)
        {
            if(!mp.count(s[r]))continue;
            
            if(--mp[s[r]]>0)continue;


            while(check(mp))
            {
                if(r-l+1<length)
                {
                    length=r-l+1;
                    res=l;
                }

                if(mp.count(s[l]))
                    mp[s[l++]]++;
                else
                    l++;
            }
        }

        return length==12345678?"":s.substr(res,length);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    string s="ADOBECODEBANC";
    string t="ABC";

    one.minWindow(s,t);

    cout<<endl;
    system("pause");
    return 0;
}
