#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include <time.h>  

#define ll long long

using namespace std;

const ll maxn=1e9,mod=1e4;

bool used[7];

int solve()
{
    int cnt=0,ans=0,t;
    for(int i=0;i<7;++i)used[i]=0;

    srand(rand()*rand()+rand()*rand());

    while(cnt<7)
    {
        t=rand()%7;

        if(!used[t])
        {
            used[t]=1;
            ++cnt;
        }

        ++ans;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    srand(time(0)+rand()-rand());

    for(ll i=1,sum=0;i<=maxn;++i)
    {
        sum+=solve();
        if(i%mod==0)cout<<sum<<' '<<sum*1.0/i<<'\n';
    }

    cout<<endl;
    system("pause");
    return 0;
}
