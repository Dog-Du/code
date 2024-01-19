#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

#define ll long long

using namespace std;

class Solution {
private:
    int distance(int i,int j,vector<vector<int>>&points)
    {
        return (points[i].front()-points[j].front())*(points[i].front()-points[j].front())
            +(points[i].back()-points[j].back())*(points[i].back()-points[j].back());
    }
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n=points.size();
        int ans=0;
        
        for(int i=0;i<n;++i)
        {
            unordered_map<int,int> mp;

            for(int j=0;j<n;++j)
            {
                if(i==j)continue;
                ++mp[distance(i,j,points)];
            }

            for(auto&PII:mp)
            {
                ans+=PII.second*(PII.second-1);
            }
        }

        return ans;
    }
};

class Solution {
private:
    int distance(int i,int j,vector<vector<int>>&points)
    {
        return (points[i].front()-points[j].front())*(points[i].front()-points[j].front())
            +(points[i].back()-points[j].back())*(points[i].back()-points[j].back());
    }
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n=points.size();
        int ans=0;
        vector<unordered_map<int,int>> vec(n);

        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(i!=j)
                    ++vec[i][distance(i,j,points)];
        
        for(auto&mp:vec)
        {
            for(auto&PII:mp)
            {
                ans+=PII.second*(PII.second-1);
            }
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<vector<int>> points={{0,0},{1,0},{2,0}};
    Solution one;
    cout<<one.numberOfBoomerangs(points);


    cout<<endl;
    system("pause");
    return 0;
}
