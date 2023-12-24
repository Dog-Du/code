using namespace std;
#include<iostream>
#include<queue>

const int maxn=1e3+10;

struct EDGE{
	int next,to,w;
}edge[maxn<<5];

int n,m,w[maxn],head[maxn],cnt=1,used[maxn],res[maxn];

void add(int x,int y,int w)
{
	edge[cnt]={head[x],y,w};
	head[x]=cnt++;
}

void spfa()
{
	for(int i=1;i<=n;++i)res[i]=1e9;
	
	res[1]=0;
	queue<int> que;
	que.push(1);
	used[1]=1;
	
	while(!que.empty())
	{
		int j=que.front();
		que.pop();
		used[j]=0;
		
		for(int i=head[j],v;i;i=edge[i].next)
		{
			v=edge[i].to;
			if(res[v]>res[j]+edge[i].w)
			{
				res[v]=res[j]+edge[i].w;
				
				if(!used[v])
				{
					que.push(v);
					used[v]=1;
				}
			}
		}
	}
	
	cout<<res[n];
}

int main()
{
	cin>>n>>m;
	
	for(int i=1;i<=n;++i)cin>>w[i];
	w[1]=0;
	
	int x,y,z;
	
	while(m--)
	{
		cin>>x>>y>>z;
		
		add(x,y,z+w[x]);
		add(y,x,z+w[y]);
	}
	
	spfa();
	return 0;
}


//
//const int maxn=1e3+10;
//
//struct EDGE{
//	int next,to,w;
//}edge[maxn<<5];
//
//struct node{
//	int now,w;
//	bool operator<(const node&it)const{
//		return w>it.w;
//	}
//};
//
//int n,m;
//int head[maxn],cnt=1,dist[maxn][maxn],used[maxn],res[maxn];
//
//void add(int x,int y,int w)
//{
//	edge[cnt]={head[x],y,w};
//	head[x]=cnt++;
//}
//
//void dj()
//{
//	for(int i=1;i<=n;++i)res[i]=1e9;
//	
//	res[1]=0;
//	priority_queue<node> que;
//	que.push({1,0});
//	
//	while(!que.empty())
//	{
//		int j=que.top().now;
//		que.pop();
//		if(used[j])continue;
//		used[j]=1;
//		
//		for(int i=head[j],v;i;i=edge[i].next)
//		{
//			v=edge[i].to;
//			
//			if(res[v]>res[j]+edge[i].w)
//			{
//				res[v]=res[j]+edge[i].w;
//				
//				if(!used[v])
//					que.push({v,res[v]});
//			}
//		}
//	}
//	
//	cout<<res[n];
//}
//
//int main()
//{
//	cin>>n>>m;
//	
//	for(int i=1,t;i<=n;++i)	
//	{
//		cin>>t;
//		for(int j=1;j<=n;++j)
//			if(i!=1&&j!=i)
//				dist[i][j]=t;
//	}
//	
//	int u,v,c;
//	
//	while(m--)
//	{
//		cin>>u>>v>>c;
//		
//		add(u,v,c+dist[u][v]);
//		add(v,u,c+dist[v][u]);
//	}
//	
//	dj();
//	return 0;
//}
