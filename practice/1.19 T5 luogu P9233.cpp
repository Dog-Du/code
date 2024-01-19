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
int n,root=1;
int color[maxn],cnt[maxn],cntcnt[maxn],son[maxn],siz[maxn];
int ans=0,flag=0;

void dfs(int now)
{
    siz[now]=1;
    int maxsize=-1;
    for(const auto&it : graph[now])
    {
        dfs(it);
        siz[now]+=siz[it];
        if(siz[it]>maxsize)
            maxsize=siz[it],son[now]=it;
    }
}

void count(int now,int k)
{
    cntcnt[cnt[color[now]]]--;
    cnt[color[now]]+=k;
    cntcnt[cnt[color[now]]]++;

    for(const auto&it : graph[now])
        if(it!=flag)count(it,k);
}

void dfs(int now,bool keep)
{
    for(const auto&it : graph[now])
        if(it!=son[now])dfs(it,false);

    if(son[now]!=0)
    {
        dfs(son[now],true);
        flag=son[now];
    }

    count(now,1);
    flag=0;

    if(cnt[color[now]]*cntcnt[cnt[color[now]]]==siz[now])
        ++ans;

    if(keep==false)
        count(now,-1);
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

    for(int i=1,y;i<=n;++i)
    {
        cin>>color[i]>>y;
        graph[y].push_back(i);
    }

    dfs(root);
    dfs(root,true);

    cout<<ans<<endl;

//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
