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
int n;
int color[maxn],cnt[maxn],son[maxn];
long long ans[maxn];
int flag,maxc;//flag标记的是当前的重儿子，防止下一层count的时候少计算重儿子。
long long sum;

//求轻重儿子。
int dfs(int now,int f)
{
    int maxsize=-1,cur=0,node_count=1;

    for(const auto& it : graph[now])
    {
        if(it==f)
            continue;
        cur=dfs(it,now);
        node_count+=cur;
        
        if(maxsize<cur)
        {
            maxsize=cur;
            son[now]=it;
        }
    }

    return node_count;
}

//进行计算和删除。
void count(int now,int fa,int k)
{
    cnt[color[now]]+=k;//加一个参数k，表示删除还是增加

    if(cnt[color[now]]>maxc)
    {
        maxc=cnt[color[now]];
        sum=color[now];//统计sum
    }
    else if(cnt[color[now]]==maxc)
        sum+=color[now];
    
    for(const auto&it : graph[now])
        if(it!=fa&&it!=flag)count(it,now,k);
}

void dfs(int now,int fa,bool keep)
{
    //写下轻儿子及其子树的答案，并删除其贡献
    for(const auto&it : graph[now])
        if(it!=son[now]&&it!=fa)dfs(it,now,false);

    //算重儿子及其子树的答案，不删除贡献
    if(son[now]!=0)
    {
        dfs(son[now],now,true);
        flag=son[now];
    }
    
    //暴力计算一遍轻儿子的贡献并合并到重儿子中
    count(now,fa,1);
    flag=0;
    ans[now]=sum;

    if(keep==false)
    {
        count(now,fa,-1);
        sum=maxc=0;//count中会修改这两个值
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

    cin>>n;;;

    for(int i=1;i<=n;++i)
        cin>>color[i];
    
    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,1);
    dfs(1,1,true);

    for(int i=1;i<=n;++i)
        cout<< ans[i] << ' ';
//-------------------------------------------------

#ifdef LOCAL
    cout << "Time Used:\n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
