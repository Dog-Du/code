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
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans=0;

        for(uint32_t i=0;i<32;++i)
            ans+=(n>>i&1)<<(31-i);
        
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    one.reverseBits(1);


    cout<<endl;
    system("pause");
    return 0;
}
