#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//基于排序
class Solution {
public:
    int hIndex(vector<int>& citations) {
        
        sort(citations.begin(),citations.end());
        reverse(citations.begin(),citations.end());

        int length=citations.size();

        for(int i=length;i>0;--i)
            if(citations[i-1]>=i)
                return i;
        
        return 0;
    }
};

//二分查找
class Solution {
public:
    int hIndex(vector<int>& citations) {
        
        int l=0,r=1000,mid,ans,sum=0;

        while(l<=r)
        {
            mid=l+r>>1;
            sum=0;

            for(auto&it:citations)
                if(it>=mid)++sum;
            
            if(sum>=mid)
                l=mid+1,ans=mid;
            else
                r=mid-1;
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
