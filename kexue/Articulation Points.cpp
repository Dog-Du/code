#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e5+10;

//参考：https://www.luogu.com.cn/problem/solution/P3388 第一篇题解，写的太好了。虽然通篇文字，但是思路清晰，推理十分完整，有心学习者均能学会。

//关节点即割点，由Tarjan算法在 时间复杂度O(n+m) 空间复杂度O(n) 下解决
//Tarjan算法基于图的DFS序及其之后的DFS树，一定是DFS，因为BFS达不到Tarjan想做的事情（子树的独立性）
//正因为是BFS可以做到以下的性质：
//1.祖先的后代性：任何非树边（变成树之后多出的部分）的两个端点具有祖先后代关系
//2.子树的独立性：节点的每个儿子（直接儿子）的子树之间没有边，这是DFS保证的（类似于染色）
//3.时间戳的区间性：子树的时间戳为一段区间（连续的一段区间）
//4.时间戳的单调性：节点的时间戳小于子树内节点的时间戳

//Tarjan就是利用DFS把图的节点分成如干个集合之后再根据这四个性质进行推理之后的一个树形DP！ 
//设x的子树为x在DFS树上的子树，包含x本身，记作T(x)。则T'(x)=V-T(x) 其中V表示点的集合

//谈论：
//1.根节点判定：
//由子树的独立性可以知道，如果一个根节点有两个以上的儿子，那么必然为割点，否则不是。

//2.非根节点判定（重点）：
// 直说结论，文章讲的十分清楚：
//对于节点x，如果x不为割点 当且仅当 x子树下存在节点y通过非树边（或者说，就是边）到达的节点的时间戳小于x的
//对上述命题取逆否 得到： 对于节点x，如果x是割点 当且仅当 x子树下任意节点y通过非树边（或者说，就是边）达到的节点的时间戳大于等于x的
//又因为子树是联通的，或者说是等价的（离散数学里的等价关系） 可以得出，
//当且仅当后半部分可以改为 x子树下存在节点y通过非树边（或者说，就是边）到达的节点的时间戳大于等于x
//进一步地，因为等价，所以我们考虑仅通过一个边到达即可，所以后半句话进一步修改：
//x子树下存在节点y劲通过一条非树边（或者说，就是边）达到的节点的时间戳大于等于x的

vector<int> edge[maxn];
int n,m,root;
//dfn表示时间戳,low表示当前子树下最小的时间戳,is_key表示是否是割点.
int dfn[maxn]={0},low[maxn]={0},cnt=0,tot=0,is_key[maxn]={0};

void dfs(int x)
{
    low[x]=dfn[x]=++cnt;
    int son=0;//这里要用一个变量记录DFS树下的子树个数，不能用edge[x].size()

    for(auto&it:edge[x])
    {
        if(dfn[it]==0)
        {
            ++son;
            dfs(it);
            low[x]=min(low[x],low[it]);

            if(low[it]>=dfn[x]&&x!=root)//非根节点，并且low[it]>=dfn[x]。这是子树
                tot+=!is_key[x],is_key[x]=1;
        }   
        else
            low[x]=min(low[x],dfn[it]);
            ////TODO:为什么是dfn[it]而不是low[it],这个值得思考
            // 分析：我的理由是，如果边出现的顺序不同的话（也就是回头看了，没有dfs向儿子搜索），low[x]会被low[it] “污染” 而与原来的意义不符
            // 比如：三个点两个边 边为 1-2 2-3 显然 2 是割点
            // 如果存图为 1:2  2:1,3（注意：1 在 3 前面，也就是在节点 2 的时候会先访问 1 再访问 3）  3:2
            // 那么在访问节点 2 的时候，显然这个时候有： low[1]=1 dfn[1]=1 low[2]=2 dfn[2]=2
            // 然后运行至else， low[2]被刷新为 1 再接着访问 节点 3 
            // 之后访问完节点 3 之后，low[1]=1 dfn[1]=1 low[2]=1 dfn[2]=2 low[3]=1 dfn[3]=3
            // 然后回溯到节点 2 ，出现 low[2]=min(low[2],low[3]) = 1 < dfn[2]=2  所以 这时 节点 2  没有被判断为 割点，这里出现了矛盾
            // 仔细考虑之后发现，错误的原因在于：在节点2的时候先去访问了节点1再去访问节点3，这个顺序错了，
            // 顺序哪里错了？ 按照Tarjan，我们应该先去访问子树才对。
            // 从另一个角度来想：这是一个树上DP。DP满足“无后效性”，所以我们当前的状态应该只能依赖于先前的状态
            // 在节点2的时候，我们去用low[1]刷新了low[2]，这是不合理的，因为因为根据low数组的定义，low[1]的值依赖于low[2]和low[3]的值
            // 那么，low[2]和low[3]就一定和low[1]无关，所以这是错误的。
            // 当然如果保证一定先访问子树再访问祖先的的话，这样做也是没有错误的。

            // 分析哪里错了之后，为什么这样是对的？
            // 当然是因为符合Tarjan算法所讲low含义，访问了所有的直接相邻的边，用他们刷新自己的low[]
            // 寻找直接相邻的边中的dfn的最小值，毕竟low最终上记录的还是dfn的最小值而已，不用dfn刷新low还用什么来刷新
            
    }

    if(x==root&&son>=2)
        tot+=!is_key[x],is_key[x]=1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    for(int i=1,x,y;i<=m;++i)
    {
        cin>>x>>y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }

    for(int i=1;i<=n;++i)
    {
        if(dfn[i]==0)
        {
            root=i;
            dfs(i);
        }
    }

    cout<<tot<<endl;

    for(int i=1;i<=n;++i)
        if(is_key[i])
            cout<<i<<' ';

    cout<<endl;
    system("pause");
    return 0;
}
