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
    int singleNumber(vector<int>& nums) {
        int ans=0;

        for(int i=0,tot;i<32;++i)
        {
            tot=0;
            for(auto&it:nums)
                tot+=it>>i&1;
                
            if(tot%3!=0)
                ans|=1<<i;
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
