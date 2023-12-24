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

    void func(int l,int r,vector<int>&nums)
    {
        while(l<r)
            swap(nums[l++],nums[r--]);
    }

    void rotate(vector<int>& nums, int k) {
        k%=nums.size();
        int length=nums.size();

        func(0,length-1,nums);
        func(0,k-1,nums);
        func(k,length-1,nums);
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<int> vec={0,1,2,3,4,5,6,7,8,9,10};

    one.rotate(vec,5);

    for(auto&it:vec)cout<<it<<' ';

    cout<<endl;
    system("pause");
    return 0;
}
