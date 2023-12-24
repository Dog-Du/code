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
    bool canJump(vector<int>& nums) {
        
        int cover=0;
        int i=0,length=nums.size();

        for(i=0;i<length&&cover>=i;++i)
            cover=max(cover,i+nums[i]);
        
        return i==length;
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
