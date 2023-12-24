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
        
        int p1=prices[0],p2;
        int ans=0;

        for(int i=1;i<prices.size();++i)
        {
            p2=prices[i];
            ans+=max(p2-p1,0);
            p1=p2;
        }

        return ans;
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
