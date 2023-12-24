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
    struct node{
        int val,id;
        bool operator<(const node&it)const{
            return val<it.val;
        }
        bool operator==(const node&it)const{
            return val==it.val;
        }
    };

    vector<int> twoSum(vector<int>& nums, int target) {
        vector<node> vec;

        for(int i=0;i<nums.size();++i)
            vec.push_back({nums[i],i});
        
        sort(vec.begin(),vec.end());

        for(int i=0,l,r,mid,t;i<vec.size();++i)
        {
            t=-1;
            l=i+1,r=vec.size()-1;

            while(l<=r)
            {
                mid=l+r>>1;

                if(vec[mid].val+vec[i].val>=target)
                    t=mid,r=mid-1;
                else
                    l=mid+1;
            }

            if(t!=-1&&vec[t].val+vec[i].val==target)
                return {vec[i].id,vec[t].id};
        }

        return {};
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
