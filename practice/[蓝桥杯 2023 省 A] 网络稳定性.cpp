using namespace std;
#include<iostream>
#include<algorithm>
#include<cmath>

const int maxn=1e5+10;
 
struct EDGE{
	int next,to,from,w;
	bool operator<(const EDGE&it)const
	{
		return w>it.w;
	}
}e[maxn<<2],edge[maxn<<1];

int n,m,q,head[maxn],cnt=1,pre[maxn],used[maxn],depth[maxn],dp[maxn][26],dist[maxn][26];

void add(int x,int y,int w)
{
	edge[cnt]={head[x],y,x,w};
	head[x]=cnt++;
}

int find(int x)
{
	return x==pre[x]?x:pre[x]=find(pre[x]);
}

void kr()
{
	sort(e+1,e+1+m);
	
	for(int i=1;i<=n;++i)pre[i]=i;
	
	for(int i=1,from,to;i<=m;++i)
	{
		from=find(e[i].from);
		to=find(e[i].to);
		
		if(from==to)continue;
		
		pre[from]=to;
		
		add(e[i].from,e[i].to,e[i].w);
		add(e[i].to,e[i].from,e[i].w);
	}
}

void dfs(int x)
{
	for(int i=1;(1<<i)<depth[x];++i)
		dp[x][i]=dp[dp[x][i-1]][i-1],
		dist[x][i]=min(dist[x][i-1],dist[dp[x][i-1]][i-1]);
		
	used[x]=1;
	for(int i=head[x],v;i;i=edge[i].next)
	{
		v=edge[i].to;
		
		if(used[v])continue;
		
		depth[v]=depth[x]+1;
		dp[v][0]=x;
		dist[v][0]=edge[i].w;
		
		dfs(v);
	}
}

void init()
{
	for(int i=1;i<=n;++i)
	{
		if(used[i])continue;
		depth[i]=1;
		dfs(i);
	}
}

int lca(int x,int y)
{
	if(depth[x]<depth[y])swap(x,y);
	
	int k=log2(depth[x]-depth[y]),ans=1e9;
	
	for(int i=k;i>=0;--i)
		if(depth[dp[x][i]]>=depth[y])
		{
			ans=min(ans,dist[x][i]);
			x=dp[x][i];
		}
		
	if(x==y)return ans;
	
	k=log2(depth[x]);
	
	for(int i=k;i>=0;--i)
		if(dp[x][i]!=dp[y][i])
		{
			ans=min(ans,dist[x][i]);
			ans=min(ans,dist[y][i]);
			x=dp[x][i];
			y=dp[y][i];
		}
	
	ans=min(ans,dist[x][0]);
	ans=min(ans,dist[y][0]);
	
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>q;
	
	for(int i=1;i<=m;++i)cin>>e[i].from>>e[i].to>>e[i].w;
	
	kr();
	
	init();
	
	int x,y;
	
	while(q--)
	{
		cin>>x>>y;
		
		if(find(x)!=find(y))cout<<-1<<'\n';
		else
		{
			cout<<lca(x,y)<<'\n';
		}
	}
	return 0;
}
