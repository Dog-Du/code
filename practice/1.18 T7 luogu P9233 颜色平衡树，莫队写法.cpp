#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=200000+10;

vector<int> graph[maxn];

int tim,n,block,t;
int siz[maxn],dfn[maxn],dfx[maxn],cntcnt[maxn],cnt[maxn],color[maxn];

struct QUEUE{
    int l,r,now;
    bool operator<(const QUEUE&other)const{
        if(l/block==other.l/block)return r<other.r;
        return l<other.l;
    }
}query[maxn];

void dfs(int now)
{
    siz[now]=1;
    dfn[now]=++tim;
    dfx[tim]=now;

    for(const auto&it : graph[now])
    {
        dfs(it);
        siz[now]+=siz[it];
    }
}

void add(int x)
{
    cntcnt[cnt[x]]--;
    cnt[x]++;
    cntcnt[cnt[x]]++;
}

void del(int x)
{
    cntcnt[cnt[x]]--;
    cnt[x]--;
    cntcnt[cnt[x]]++;
}

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

    cin>>n;

    block=sqrt(n);

    for(int i=1,y;i<=n;++i)
    {
        cin>>color[i]>>y;
        graph[y].push_back(i);
    }

    dfs(1);

    for(int i=1;i<=n;++i)
        query[i]={dfn[i],dfn[i]+siz[i]-1,i};
    
    sort(query+1,query+1+n);

    int ans=0;
    add(color[1]);

    for(int i=1,curl=1,curr=1;i<=n;++i)
    {
        while(curl<query[i].l)del(color[dfx[curl++]]);
        while(curl>query[i].l)add(color[dfx[--curl]]);
        while(curr<query[i].r)add(color[dfx[++curr]]);
        while(curr>query[i].r)del(color[dfx[curr--]]);
        
        int c=cnt[color[dfx[query[i].l]]],f=cntcnt[c];

        if(c*f==curr-curl+1)
            ++ans;
    }

    cout<<ans<<endl;
//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
