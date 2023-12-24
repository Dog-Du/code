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
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> mp;
        int ans=0,n=s.size();

        for(int l=0,r=0;r<n;++r)
        {
            if(mp[s[r]])
            {
                while(s[l]!=s[r])
                {
                    mp[s[l++]]--;
                }

                mp[s[l++]]=0;
            }

            mp[s[r]]++;
            ans=max(ans,r-l+1);
        }

        return ans;
    }
};

// 动态规划写法
// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         int ans=0,n=s.size();
//         unordered_map<char,int> pre;
//         vector<int> dp(n,-1);

//         for(int i=0;i<n;++i)
//         {
//             if(pre.count(s[i]))
//             {
//                 dp[i]=max(dp[i-1],pre[s[i]]);
//             }
//             else if(i>0)
//                 dp[i]=dp[i-1];

//             pre[s[i]]=i;
//             ans=max(ans,i-dp[i]);
//         }

//         return ans;
//     }
// };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    string s="tmmzuxt";
    one.lengthOfLongestSubstring(s);


    cout<<endl;
    system("pause");
    return 0;
}
