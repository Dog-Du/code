#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define ll long long

using namespace std;

//哈西方法
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int> mp;

        for(int i=0;i<nums.size();++i)
        {
            if(mp.count(nums[i]))
            {
                if(abs(i-mp[nums[i]])<=k)return true;
                else mp[nums[i]]=i;
            }
            else    
                mp[nums[i]]=i;
        }

        return false;
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
