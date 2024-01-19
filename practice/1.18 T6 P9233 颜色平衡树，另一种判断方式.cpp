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
int color[maxn],son[maxn],t[2][maxn],siz[maxn];
//t[0][x]表示颜色x出现了几次，t[1][x]表示次数x出现的次数。

int ans=0,flag;//MINN,MAXN维护的是颜色出现的次数

void add(int x)
{
    t[1][t[0][x]]--;
    t[0][x]++;
    t[1][t[0][x]]++;
}

void del(int x)
{
    t[1][t[0][x]]--;
    t[0][x]--;
    t[1][t[0][x]]++;
}

void add_k(int now)
{
    add(color[now]);

    for(const auto&it : graph[now])
        if(it!=flag)add_k(it);
}


void del_k(int now)
{
    del(color[now]);

    for(const auto&it : graph[now])
        if(it!=flag)del_k(it);
}

void dfs(int now)
{
    int maxsize=-1;
    siz[now]=1;

    for(const auto&it : graph[now])
    {
        dfs(it);
        siz[now]+=siz[it];
        if(siz[it]>maxsize)
        {
            maxsize=siz[it];
            son[now]=it;
        }
    }
}


void dfs(int now,bool keep)
{
    for(const auto& it : graph[now])
        if(it != son[now])
            dfs(it,false);
    
    if(son[now]!=0)
    {
        dfs(son[now],true);
        flag=son[now];
    }

    add_k(now);
    flag=0;
    
    //这句话的含义是：color[now]出现的频次*这个频次的频次 ==  siz[now]，
    //则说明颜色出现最多的次数和颜色出现最小的次数相等。
    //原因是：如果存在一个颜色，其出现的频次不等于color[now]出现的频次，
    //那么，这个算式是小于size[now]的。
    if(t[0][color[now]]*t[1][t[0][color[now]]]==siz[now])
        ++ans;

    if(keep==false)
    {
        del_k(now);
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

    for(int i=1,f;i<=n;++i)
    {
        cin>>color[i]>>f;
        graph[f].push_back(i);
    }

    dfs(root);
    dfs(root,true);

    cout << ans << endl;
//-------------------------------------------------

#ifdef LOCAL
    cout << "Time Used:\n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
