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
    int findPeakElement(vector<int>& nums) {
        if(nums.size()==1)return 0;

        int n=nums.size();
        for(int i=1;i<n-1;++i)
        {
            if(nums[i]>nums[i-1]&&nums[i]>nums[i+1])return i;
        }

        if(nums[0]>nums[1])return 0;
        if(nums[n-1]>nums[n-2])return n-1;
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
