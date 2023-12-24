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
    int maxArea(vector<int>& height) {
          int n=height.size(),ans=0;

          vector<int> lmax(n,-1),rmax(n,-1);
        lmax.front()=height.front();
        rmax.back()=height.back();

        for(int i=1;i<n;++i)
            lmax[i]=max(lmax[i-1],height[i]);
        
        for(int i=n-2;i>=0;--i)
            rmax[i]=max(rmax[i+1],height[i]);

        for(int i=0,l,r,mid,t1,t2;i<n;++i)
        {
            l=0,r=i-1,t1=i,t2=i;

            while(l<=r)
            {
                mid=l+r>>1;

                if(lmax[mid]>=height[i])
                    r=mid-1,t1=mid;
                else
                    l=mid+1;
            }

            l=i+1,r=n-1;

            while(l<=r)
            {
                mid=l+r>>1;

                if(rmax[mid]>=height[i])
                    l=mid+1,t2=mid;
                else
                    r=mid-1;
            }

            ans=max(ans,height[i]*max(i-t1,t2-i));
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
