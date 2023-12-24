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
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(),points.end(),
        [](vector<int>&a,vector<int>&b){return a.front()<b.front();});

        int ans=(points.size()>0?1:0);

        for(int i=1,n=points.size();i<n;++i)
        {
            if(points[i].front()>points[i-1].back())
            {
                ++ans;
            }
            else
            {
                points[i].back()=min(points[i-1].back(),points[i].back());
            }
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
