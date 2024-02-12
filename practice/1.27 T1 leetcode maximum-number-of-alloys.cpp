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
    bool check(int n,int k,int budget,vector<vector<int>>& composition,vector<int>& stock,vector<int>& cost,long long mid)
    {
        for(const auto& it:composition)
        {
            long long sum=budget;
            bool flag=true;

            for(int i=0;i<n;++i)
            {
                long long c=(mid*it[i]-stock[i])*cost[i];
                if(c>0)
                    sum-=c;
                
                if(sum<0)
                {
                    flag=false;
                    break;
                }
            }

            if(flag)
                return true;
        }

        return false;
    }
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        int l=0,r=1e9,mid,ans=0;

        while(l<=r)
        {
            mid=l+r>>1;
            
            if(check(n,k,budget,composition,stock,cost,mid))
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

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    int n=2,k=3,budget=10;
    vector<vector<int>> composition={{2,1},{1,2},{1,1}};
    vector<int> stock={1,1};
    vector<int> cost={5,5};
    Solution one;
    cout<<one.maxNumberOfAlloys(n,k,budget,composition,stock,cost)<<endl;


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
