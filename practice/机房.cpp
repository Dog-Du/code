using namespace std;
#include<iostream>
#include<cmath>

//我们这里可以把1号点当做树根root，然后使用dist[x]表示x点发送消息到root所需要的时间。 很显然，x发送出去的时候经过自身的延迟后到达另外一个点，另外一个点在经过延迟到达下一个点，以此类推。。。
//那么任意两个点之间的距离一般就是使用dist[x] + dist[y] - 2 * dist[lca(a, b)] 但是对于本题而言，当减去两倍的最近公共祖p先到root的距离时，就会把自身的 一个延迟多减 了一次， 所以还需要 加上p的出度。
// 所以本题正确计算距离的公式应该为： d = (dist[x] + dist[y] - 2 * dist[p] + dg[p]) 其中p表示x和y的最近公共祖先，dg[p]表示p点的出度

const int maxn=1e5+10;

struct EDGE{
	int next,to;	
}edge[maxn<<3];

int head[maxn],cnt=1,n,m,ind[maxn],dp[maxn][20],dist[maxn],used[maxn],depth[maxn];

void add(int x,int y)
{
	edge[cnt]={head[x],y};
	head[x]=cnt++;
	ind[x]++;
}

void dfs(int x)
{
	for(int i=1;(1<<i)<depth[x];++i)
		dp[x][i]=dp[dp[x][i-1]][i-1];
	
	used[x]	=1;
	for(int i=head[x],v;i;i=edge[i].next)
	{
		v=edge[i].to;
		
		if(used[v])continue;
		depth[v]=depth[x]+1;
		dp[v][0]=x;
		dist[v]=dist[x]+ind[v];
		
		dfs(v);
	}
}

int lca(int x,int y)
{
	if(depth[x]<depth[y])	swap(x,y);
	
	int t1=x,t2=y;
	int k=log2(depth[x]-depth[y]);
	
	for(int i=k;i>=0;--i)
		if(depth[dp[x][i]]>=depth[y])
			x=dp[x][i];
	
	if(x==y)return dist[t1]+dist[t2]-2*dist[x]+ind[x];
	
	k=log2(depth[x]);
	
	for(int i=k;i>=0;--i)
		if(dp[x][i]!=dp[y][i])
		{
			x=dp[x][i];
			y=dp[y][i];
		}
		
	x=dp[x][0];
	
	return dist[t1]+dist[t2]-2*dist[x]+ind[x];
}

int main()
{
	cin>>n>>m;
	
	for(int i=1,x,y;i<=n-1;++i)
	{
		cin>>x>>y;
		
		add(x,y);
		add(y,x);
	}
	
	depth[1]=1;
	dfs(1);
	
	int x,y;
	while(m--)
	{
		cin>>x>>y;
		
		cout<<lca(x,y)<<'\n';
	}
	return 0;
}
