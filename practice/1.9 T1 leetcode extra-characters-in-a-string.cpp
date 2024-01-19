#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>

#define ll long long

using namespace std;

//dp 这个dp不知道为什么感觉很简单，很快就推出来了。
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n=s.size(); 
        unordered_set<string> se(dictionary.begin(),dictionary.end());
        vector<int> dp(n+1,(int)1e5);
        dp.front()=0;

        for(int i=0;i<n;++i)
        {
            for(int j=0;j<=i;++j)
            {
                if(se.count(s.substr(j,i-j+1)))
                    dp[i+1]=min(dp[i+1],dp[j]);
                else
                    dp[i+1]=min(dp[i+1],dp[j]+i-j+1);
            }
        }

        return dp.back();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
