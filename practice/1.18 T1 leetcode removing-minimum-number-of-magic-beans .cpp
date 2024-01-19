#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>

#define ll long long

using namespace std;

//贪心
class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        sort(beans.begin(),beans.end());
        long long ans=accumulate(beans.begin(),beans.end(),(long long)0),
            sum=ans,cur=0;

        for(long long i=0,n=beans.size();i<n;++i)
        {
            ans=min(ans,cur+sum-beans[i]*(n-i));
            sum-=beans[i];
            cur+=beans[i];
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
    cout << "Time Used: " << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
