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
    int findRotateSteps(string ring, string key) {
        int n=ring.size(),m=key.size();
        vector<vector<int>> dp(m,vector<int>(n,100*1000));//第i个key字母时，ring中第j个字符在12:00时的最短操作
        vector<int> pos[26];//字母x的位置有哪些

        for(int i=0;i<n;++i)
            pos[ring[i]-'a'].push_back(i);
        
        for(const auto& it : pos[key[0]-'a'])
            dp[0][it]=min(it,n-it)+1;
        
        for(int i=1;i<m;++i)
        {
            for(const auto&j:pos[key[i]-'a'])
            {
                for(const auto&k:pos[key[i-1]-'a'])
                {
                    dp[i][j]=min(dp[i][j],dp[i-1][k]+1+min(abs(j-k),n-abs(j-k)));
                }
            }
        }

        return *min_element(dp[m-1].begin(),dp[m-1].end());
    }
};

//贪心，错误解答。
class Solution {
private:
    pair<int,int> findpos(string &ring,int i,char c)
    {
        int cnt1=0,pos1=i,cnt2=0,pos2=i,n=ring.size();
        
        while(ring[pos1]!=c)
        {
            ++cnt1;
            pos1=(pos1+1)%n;
        }

        while(ring[pos2]!=c)
        {
            ++cnt2;
            pos2=(pos2+n-1)%n;
        }

        if(cnt1<cnt2)return make_pair(cnt1,pos1);
        return make_pair(cnt2,pos2);
    }
public:
    int findRotateSteps(string ring, string key) {
        int ans=0,pos=0;
        
        for(const auto& it : key)
        {
            auto tmp=findpos(ring,pos,it);
            pos=tmp.second;
            ans+=tmp.first+1;
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
