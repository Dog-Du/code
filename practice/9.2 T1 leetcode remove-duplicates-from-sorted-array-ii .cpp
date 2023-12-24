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
    int removeDuplicates(vector<int>& nums) {
        int l=2,r=2,length=nums.size();

        while(r<length)
        {
            
            if(!(nums[r]==nums[l-1]&&nums[r]==nums[l-2]))
                nums[l++]=nums[r];
            ++r;

            for(int i=0;i<length;++i)cout<<nums[i]<<' ';
            cout<<endl;
        }

        return min(l,length);

    }
};


// //暴力标记删除法
// class Solution {
// public:
//     int removeDuplicates(vector<int>& nums) {
//         int l=0,r=0,length=nums.size(),maxn=1e9;

//         while(r<length)
//         {
//             while(r<length&&nums[l]==nums[r])
//             {
//                 if(r-l+1>2)nums[r]=maxn;
//                 ++r;
//             }
//             l=r;
//         }

//         l=0,r=0;

//         while(r<length)
//         {
//             if(nums[r]==maxn)++r;
//             else
//                 nums[l++]=nums[r++];
//         }

//         return l;
//     }
// };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<int> it={0,0,1,1,1,1,2,3,3};

    cout<<one.removeDuplicates(it)<<endl;


    cout<<endl;
    system("pause");
    return 0;
}
