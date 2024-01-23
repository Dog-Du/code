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

int n,root=1,tim=0,block;
int color[maxn],siz[maxn],dfn[maxn],dfx[maxn];
int cnt[maxn],cntcnt[maxn];

struct QUERY{
    int l,r;
    bool operator<(const QUERY& other)const{
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

void add(int x,int k)
{
    cntcnt[cnt[x]]--;
    cnt[x]+=k;
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

    dfs(root);

    for(int i=1;i<=n;++i)
        query[i]={dfn[i],dfn[i]+siz[i]-1};

    sort(query+1,query+1+n);

    int ans=0,l=1,r=1;
    add(color[dfn[1]],1);

    for(int i=1,c,f;i<=n;++i)
    {
        while(l<query[i].l)add(color[dfx[l++]],-1);
        while(l>query[i].l)add(color[dfx[--l]],1);
        while(r<query[i].r)add(color[dfx[++r]],1);
        while(r>query[i].r)add(color[dfx[r--]],-1);

        c=cnt[color[dfx[query[i].l]]],f=cntcnt[c];

        if(c*f==query[i].r-query[i].l+1)
            ++ans;
    }

    cout<<ans;
//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
