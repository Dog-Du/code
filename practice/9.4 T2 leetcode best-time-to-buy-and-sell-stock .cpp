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

    int maxProfit(vector<int>& prices) {

        int length=prices.size();
        vector<vector<int>> dp(length+1,vector<int>(2,0))        ;

        dp[0][0]=-prices[0];
        dp[0][1]=0;

        for(int i=1;i<=length-1;++i){
            
            dp[i][0]=max(dp[i-1][0],-prices[i]);

            dp[i][1]=max(dp[i-1][1],dp[i-1][0]+prices[i]);
        }

        return dp[length-1][1];
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
