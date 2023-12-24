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
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int l=newInterval.front(),r=newInterval.back();
        bool flag=0;

        for(auto&it:intervals)
        {
            if(it.front()>r)
            {
                if(!flag)
                {
                    flag=1;
                    res.push_back({l,r});
                }
                res.push_back(it);
            }
            else if(it.back()<l)
            {
                res.push_back(it);
            }
            else
            {
                l=min(l,it.front());
                r=max(r,it.back());
            }
        }

        if(!flag)res.push_back({l,r});
        return res;
    }
};

// class Solution {
// public:

//     int search(vector<vector<int>> & vec,int x)
//     {
//         int l=0,r=vec.size()-1,mid,ans=-1;

//         while(l<=r)
//         {
//             mid=l+r>>1;

//             if(vec[mid].front()<=x)
//                 l=mid+1,ans=mid;
//             else
//                 r=mid-1;
//         }

//         return ans;
//     }

//     vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
//         if(intervals.size()==0)return {newInterval};

//         intervals.insert(intervals.begin(),{-1,-1});
//         intervals.push_back({(int)1e5+1,(int)1e5+1});

//         int pos=search(intervals,newInterval.front());
//         int t=search(intervals,newInterval.back());
        
//         int l=(intervals[pos].back()<newInterval.front()?newInterval.front():intervals[pos].front());
//         int r=max(intervals[t].back(),newInterval.back());

//         intervals.erase(intervals.begin()+pos+(intervals[pos].back()<newInterval.front()?1:0),
//                 intervals.begin()+t+1);

//         intervals.insert(intervals.begin()+pos+(intervals[pos].back()<newInterval.front()?1:0),{l,r});

//         intervals.pop_back();
//         intervals.erase(intervals.begin(),intervals.begin()+1);
//         sort(intervals.begin(),intervals.end(),
//         [](vector<int>&a,vector<int>&b){return a.front()<b.front();});
//         return intervals;
//     }
// };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    vector<vector<int>> vec={{1,5}};
    vector<int> vvv={0,3};

    Solution one;
    one.insert(vec,vvv);

    for(auto &it:vec)
    {
        for(auto&iter:it)
            cout<<iter<<' ';
        cout<<endl;
    }

    cout<<endl;
    system("pause");
    return 0;
}
