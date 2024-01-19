#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e5+10;

vector<int> graph[maxn];

int n,root=1;

int flag=0,maxcnt=0,son[maxn],cnt[maxn],color[maxn];

long long sum=0,ans[maxn];

int dfs(int now,int fa)
{
    int node_count=1,maxsize=-1,cur;

    for(const auto&it : graph[now])
    {
        if(it==fa)continue;
        cur=dfs(it,now);

        node_count+=cur;

        if(cur>maxsize)
        {
            maxsize=cur;
            son[now]=it;
        }
    }
    return node_count;
}

void count(int now,int fa,int k)
{
    cnt[color[now]]+=k;

    if( cnt[color[now]] > maxcnt )
        maxcnt=cnt[color[now]],sum=color[now];
    else if(cnt[color[now]]==maxcnt)
        sum+=color[now];
    
    for(const auto&it : graph[now])
        if(it!=fa&&it!=flag)count(it,now,k);
}

void dfs(int now,int fa,bool keep)
{
    for(const auto&it : graph[now])
        if(it!=fa&&it!=son[now])
            dfs(it,now,false);
    
    if(son[now]!=0)
    {    
        dfs(son[now],now,true);
        flag=son[now];
    }
    
    count(now,fa,1);

    ans[now]=sum;
    flag=0;
    
    if(keep==false)
    {
        count(now,fa,-1);
        sum=maxcnt=0;
    }
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

    for(int i=1;i<=n;++i)
        cin>>color[i];

    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(root,root);
    dfs(root,root,true);

    for(int i=1;i<=n;++i)
        cout<<ans[i]<<' ';

//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
