using namespace std;
#include<iostream>
#include<cmath>

//����������԰�1�ŵ㵱������root��Ȼ��ʹ��dist[x]��ʾx�㷢����Ϣ��root����Ҫ��ʱ�䡣 ����Ȼ��x���ͳ�ȥ��ʱ�򾭹�������ӳٺ󵽴�����һ���㣬����һ�����ھ����ӳٵ�����һ���㣬�Դ����ơ�����
//��ô����������֮��ľ���һ�����ʹ��dist[x] + dist[y] - 2 * dist[lca(a, b)] ���Ƕ��ڱ�����ԣ�����ȥ���������������p�ȵ�root�ľ���ʱ���ͻ������� һ���ӳٶ�� ��һ�Σ� ���Ի���Ҫ ����p�ĳ��ȡ�
// ���Ա�����ȷ�������Ĺ�ʽӦ��Ϊ�� d = (dist[x] + dist[y] - 2 * dist[p] + dg[p]) ����p��ʾx��y������������ȣ�dg[p]��ʾp��ĳ���

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
