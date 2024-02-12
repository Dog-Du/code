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
    struct node{
        int to,w;
        node():to(0),w(0){}
        node(int x,int y):to(x),w(y){}
    };

    static const int maxn=1e4+5;
    vector<node> graph[maxn];//邻接表存图

    int root=0;//root设置为0

    int son[maxn]={0},depth[maxn]={0};
    //topcnt表示从当前跳到top时，这部分中间各个权重个数，chaincnt则表示节点个数
    int top[maxn]={0},topcnt[maxn][26]={0},chaincnt[maxn]={0};

    node fa[maxn];

    void add_edge(vector<vector<int>>&edges)
    {
        for(const auto & it: edges)
        {
            graph[it[0]].push_back({it[1],it[2]-1});//-1，让它从0-25
            graph[it[1]].push_back({it[0],it[2]-1});
        }
    }

    int dfs1(int now)//返回值为子树节点个数，因为不需要子树个数，所以不额外设置siz[maxn]数组
    {
        depth[now]=depth[fa[now].to]+1;
        int maxsize=-1,cur=0,node_count=1;

        for(const auto&it : graph[now])
        {
            if(it.to==fa[now].to)continue;

            fa[it.to]={now,it.w};//为了方便，设置父亲

            cur=dfs1(it.to);

            node_count+=cur;

            if(cur>maxsize)
                maxsize=cur,son[now]=it.to;
        }

        return node_count;
    }

    void dfs2(int now,int t,bool keep)//keep表示是否从继承父亲。
    {
        top[now]=t;

        if(keep)//true表示继承父亲，下面是继承的过程
        {
            chaincnt[now]=chaincnt[fa[now].to]+1;

            for(int i=0;i<26;++i)
                topcnt[now][i]=topcnt[fa[now].to][i];

            ++topcnt[now][fa[now].w];
        }

        if(son[now]==0)//没有孩子，直接返回
            return;
        
        dfs2(son[now],t,true);//有重孩子，先走重孩子，让它继承

        for(const auto&it : graph[now])
        {
            if(it.to==son[now]||it.to==fa[now].to)continue;
            dfs2(it.to,it.to,false);//重新开一条链，不让它继承
        }
    }

    void init(vector<vector<int>>& edges)//预处理
    {
        add_edge(edges);//边
        dfs1(root);
        dfs2(root,root,true);
    }

    int query(int x,int y)//询问，显然需要修改的节点个数=从x到y的边数-x到y的边数的最大值
    {
        int cnt[26]={0},cur=0,maxsize=-1;//cur表示链上的节点个数，cnt表示各个权重的个数

        //模板：技巧：保证x在下，y在上
        //如果不在一条链上：
        while(top[x]!=top[y])
        {
            if(depth[top[x]]<depth[top[y]])//用x表示浅的
                swap(x,y);

            for(int i=0;i<26;++i)
                cnt[i]+=topcnt[x][i];
            cur+=chaincnt[x]+1;//不要忘了加1，这是移动到x的top的父亲所需要的
            ++cnt[fa[top[x]].w];//这个也是从x到top的父亲所需要的

            x=fa[top[x]].to;
        }

        if(depth[x]<depth[y])
            swap(x,y);
        
        //已经在一条链上了，x在下，y在上，两者top是一样的，
        //那么从x到y，等于 先从x到top，再从top到y，相减即可。

        for(int i=0;i<26;++i)
            maxsize=max(maxsize,topcnt[x][i]-topcnt[y][i]+cnt[i]);

        cur+=chaincnt[x]-chaincnt[y];

        return cur-maxsize;
    }

public:
    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        init(edges);

        vector<int> ans;
        for(const auto&it : queries)
            ans.push_back(query(it[0],it[1]));

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
