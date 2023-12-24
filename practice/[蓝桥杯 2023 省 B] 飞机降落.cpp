using namespace std;
#include<iostream>
#include<algorithm>
#include<cstring>

//贪心不出来，直接爆搜
 
struct node{
	int l,r,v;
	bool operator<(const node&it)const
	{
		return r<it.r;
	}
}node[100005];

int used[20];

bool dfs(int x,int cur,int stop)//cur表示现在最晚的时间 
{	
	if(x>stop)return true;//如果全部起飞，直接true 
	
	for(int i=1;i<=stop;++i)
	{
		if(used[i]||cur>node[i].r)continue;
		
		used[i]=1;
		if(dfs(x+1,max(cur,node[i].l)+node[i].v,stop))return true;
		used[i]=0;
	}
	
	return false;
}

bool solve(int n)
{
	memset(used,0,sizeof used);
	sort(node+1,node+1+n);
	return dfs(1,0,n);
}

int main()
{
	int t;
	cin>>t;
	
	while(t--)
	{
		int n;
		cin>>n;
		
		for(int i=1;i<=n;++i)
		{
			cin>>node[i].l>>node[i].r>>node[i].v;
			node[i].r+=node[i].l;
		}
		
		cout<< (solve(n)?"YES":"NO")<<'\n';
	}
	return 0;
}
