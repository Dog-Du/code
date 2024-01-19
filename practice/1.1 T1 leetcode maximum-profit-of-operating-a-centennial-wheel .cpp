#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//模拟
class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int profit=0,cnt=1,ans=0,i=-1,n=customers.size();
        int custom=customers[0];

        while (custom>0||cnt<n)//cnt<n这个不能忘.
        {
            int cost=min(custom,4);
            custom-=cost;

            profit+=boardingCost*cost-runningCost;

            if(profit>ans)
                ans=profit,i=cnt;

            if(cnt<n)
                custom+=customers[cnt];
            
            ++cnt;
        }
        
        return i;
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
