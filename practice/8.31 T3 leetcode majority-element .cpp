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
    int majorityElement(vector<int>& nums) {

        int cnt=0,m=nums.front();

        for(auto&it:nums)
        {
            if(cnt==0)
                m=it;

            if(it==m)++cnt;
            else --cnt;
        }

        return m;
    }
};

//法一，排序+双指针
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int length=nums.size();

        sort(nums.begin(),nums.end());

        int l=0,r=0;

        while(r<length)
        {
            while(r<length&&nums[r]==nums[l])++r;//r<length 方式溢出

            if(r-l>length/2)return nums[l];

            l=r;
        }

        return -1;
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
