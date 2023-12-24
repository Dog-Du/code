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
    int maxProfit(int k, vector<int>& prices) {
        int n=prices.size();
        k=min(k,n/2);//交易次数是k和n/2的最小值

        //buy表示第i次买之后的最大收益，sell表示第i次卖之后的最大收益。
        vector<int> buy(k+1,(int)-1e9),sell(k+1,0);

        for(auto&it:prices)
        {
            for(int i=1;i<=k;++i)
            {
                buy[i]=max(buy[i],sell[i-1]-it);
                sell[i]=max(sell[i],buy[i]+it);
            }
        }

        return sell.back();
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
