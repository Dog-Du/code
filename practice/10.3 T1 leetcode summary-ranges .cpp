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

    string func(int x)
    {
        if(!x)return "0";
        string ans;
        bool flag=(x<0);
        x=abs(x);

        while(x)
        {
            ans.push_back(x%10+'0');
            x/=10;
        }

        if(flag)ans.push_back('-');

        reverse(ans.begin(),ans.end());
        return ans;
    }

    vector<string> summaryRanges(vector<int>& nums) {
        int n=nums.size();
        vector<string> ans;

        for(int l=0,r=0;r<n;)
        {
            while(r+1<n&&nums[r+1]==nums[r]+1)
                ++r;
            
            if(nums[r]==nums[l])ans.push_back(func(nums[l]));
            else ans.push_back(func(nums[l])+"->"+func(nums[r]));

            l=++r;
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
