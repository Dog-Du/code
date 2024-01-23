#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    int n;

    bool check(vector<int>&nums,int k,int maxsum)
    {
        for(int cursum=0;const auto& it : nums)
        {
            cursum+=it;

            if(cursum>maxsum)
            {
                cursum=it;
                if(k--==0)return false;
            }
        }

        return k>0;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        int l=0,r=1e9,mid,ans=0;
        n=nums.size();

        for(const auto&it : nums)
            ans=max(it,ans);
        
        l=ans;

        while(l<=r)
        {
            mid=l+r>>1;

            if(check(nums,k,mid))
                r=mid-1,ans=mid;
            else
                l=mid+1;
        }

        return ans;
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

    vector<int> nums={7,2,5,10,8};
    Solution one;
    one.splitArray(nums,2);


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
