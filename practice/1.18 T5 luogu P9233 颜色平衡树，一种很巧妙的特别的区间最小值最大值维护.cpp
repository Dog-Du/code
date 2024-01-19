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
int color[maxn],son[maxn],t[2][maxn];
//t[0][x]表示颜色x出现了几次，t[1][x]表示次数x出现的次数。

int ans=0,flag,MINN=maxn+1,MAXN=0;//MINN,MAXN维护的是颜色出现的次数

void add(int x)
{
    t[1][t[0][x]]--;
    t[0][x]++;
    t[1][t[0][x]]++;

    if(t[0][x]>MAXN)MAXN=t[0][x];
    if(t[0][x]<MINN)MINN=t[0][x];

    if(!t[1][MINN])++MINN;//如果增加了x之后，频次MINN的没有了，说明频次MINN的全部都变成了MINN+1,因此MINN++;
}

void del(int x)
{
    t[1][t[0][x]]--;
    t[0][x]--;
    t[1][t[0][x]]++;
    
    if(t[0][x]>0&&t[0][x]<MINN)MINN=t[0][x];
    if(t[0][x]>MAXN)MAXN=t[0][x];

    if(!t[1][MAXN])MAXN--;//同理，如果删去x之后，频次MAXN没有了，说明频次MAXN的消失了，
    //但因为是删除x之后MAXN才消失，所以必定是x导致的，所以频次仅减1
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
int dfs(int now)
{
    int maxsize=-1,cur=0,node_count=1;

    for(const auto&it : graph[now])
    {
        cur=dfs(it);
        node_count+=cur;
        if(cur>maxsize)
        {
            maxsize=cur;
            son[now]=it;
        }
    }

    return node_count;
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
    
    if(MINN==MAXN)
        ++ans;

    if(keep==false)
    {
        del_k(now);
        MINN=maxn+10;
        MAXN=0;
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
