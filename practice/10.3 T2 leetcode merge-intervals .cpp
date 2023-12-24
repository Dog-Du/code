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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans;

        sort(intervals.begin(),intervals.end(),
            [](vector<int>&a,vector<int>&b){return a.front()<b.front();});
        
        for(int i=1,n=intervals.size();i<n;++i)
        {
            if(intervals[i].front()<=intervals[i-1].back())
            {
                intervals[i].front()=min(intervals[i].front(),intervals[i-1].front());
                intervals[i].back()=max(intervals[i].back(),intervals[i-1].back());
            }
            else
            {
                ans.push_back(intervals[i-1]);
            }
        }

        ans.push_back(intervals.back());
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
