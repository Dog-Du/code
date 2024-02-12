#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define ll long long

using namespace std;


//桶，
//思路：
//1.选择一个数x，将它作为最后的那个相同的数字，那么 次数=相邻的两个距离的最大值/2
//2.答案=所有数字相邻距离的最大值中的最小者/2
//3.使用桶进行分离可以加速
//4.时间复杂度：O(n) 空间复杂度：O(n)

class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        int n=nums.size();
        unordered_map<int,vector<int>> mp;

        for(int i=0;i<n;++i)
            mp[nums[i]].push_back(i);
        
        int ans=n;

        for(const auto&it:mp)
        {
            int cur=0;

            for(int i=1;i<it.second.size();++i)
            {
                cur=max(cur,abs(it.second[i]-it.second[i-1]));
            }

            cur=max(cur,n-it.second.back()+it.second.front());

            ans=min(ans,cur);
        }

        return ans/2;
    }
};

//贪心,错解
class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        unordered_map<int,int> mp;

        for(const auto&it:nums)
            ++mp[it];
        
        int maxnums,maxsize=-1;

        for(const auto&it:mp)
        {
            if(it.second>maxsize)
            {
                maxsize=it.second;
                maxnums=it.first;
            }
        }

        int beg=0,end=0,n=nums.size();

        if(maxsize==1)
            return n/2;


        for(int i=0;i<n;++i)
            if(nums[i]==maxnums)
            {
                beg=i;
                break;
            }
        
        for(int i=n-1;i>=0;--i)
            if(nums[i]==maxnums)
            {
                end=i;
                break;
            }
        
        int distance=0;

        for(int l=beg,r=beg;r<=end;++r)
        {
            if(nums[r]==maxnums)
            {
                distance=max(distance,r-l);
                l=r+1;
            }
        }

        return max((beg+n-1-end)/2,(distance+1)/2);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
