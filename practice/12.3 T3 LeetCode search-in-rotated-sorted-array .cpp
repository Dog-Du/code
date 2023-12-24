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
    int search(vector<int>& nums, int target) {
        if(nums.size()==1)return -(nums.front()!=target);

        int n=nums.size(),l=0,r=n-1,mid,t=0;

        while(l<=r)
        {
            mid=l+r>>1;
            if(nums[mid]<=nums.back())r=mid-1;
            else l=mid+1,t=mid;
        }

        auto iter1=lower_bound(nums.begin(),nums.begin()+t+1,target);
        auto iter2=lower_bound(nums.begin()+t+1,nums.end(),target);
        if(iter1!=nums.end()&&*iter1==target)return iter1-nums.begin();
        if(iter2!=nums.end()&&*iter2==target)return iter2-nums.begin();
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
