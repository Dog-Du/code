#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_set>

#define ll long long

using namespace std;

//找最小的，如果存在比他小的就continue，然后依次进行寻找
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> se(nums.begin(),nums.end());

        int ans=0;

        for(auto&it:se)
        {
            int cur=it;

            if(!se.count(cur-1))
                while(se.count(cur+1))
                    ++cur;
            
            ans=max(ans,cur-it+1);
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<int> nums={0,3,7,2,5,8,4,6,0,1};
    Solution one;
    one.longestConsecutive(nums);


    cout<<endl;
    system("pause");
    return 0;
}
