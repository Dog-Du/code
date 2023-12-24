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
    int uniquePathsWithObstacles(vector<vector<int>>& g) {
        int n=g.size(),m=g.front().size();

        vector<vector<int>> dp(n,vector<int>(m,0));

        for(int i=0;i<n;++i)
            if(g[i][0])break;
            else
                dp[i][0]=1;
        
        for(int i=0;i<m;++i)
            if(g[0][i])break;
            else
                dp[0][i]=1;
        
        for(int i=1;i<n;++i)
        {
            for(int j=1;j<m;++j)
            {
                if(g[i][j])continue;
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }

        return dp.back().back();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<vector<int>> vec={{0,0}};
    Solution one;
    one.uniquePathsWithObstacles(vec);


    cout<<endl;
    system("pause");
    return 0;
}
