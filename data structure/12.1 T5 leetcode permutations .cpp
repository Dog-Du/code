#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    vector<int> path,used;
    vector<vector<int>> ans;
    int n;
    void dfs(int now,vector<int>&nums)
    {
        if(now==nums.size())
        {
            ans.push_back(path);
            return;
        }

        for(int i=0;i<n;++i)
        {
            if(used[i])continue;
            used[i]=1;
            path.push_back(nums[i]);
            dfs(now+1,nums);
            path.pop_back();
            used[i]=0;
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        n=nums.size();
        used.resize(n,0);
        dfs(0,nums);
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
