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
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        long long ans=-1;
        int n=maxHeights.size();

        for(int i=0;i<n;++i)
        {
            long long sum=maxHeights[i];
            int last=maxHeights[i];

            for(int j=i+1;j<n;++j)
            {
                last=min(last,maxHeights[j]);
                sum+=last;
            }

            last=maxHeights[i];
           
            for(int j=i-1;j>=0;--j)
            {
                last=min(last,maxHeights[j]);
                sum+=last;
            }

            ans=max(ans,sum);
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

    


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
