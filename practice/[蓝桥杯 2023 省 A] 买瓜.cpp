using namespace std;
#include<iostream>
#include<algorithm>
#include<unordered_map>
#define ll long long

ll n,m,a[50];
int ans=114514;
unordered_map<ll,int> mp;

void dfs1(int x,int step,ll now,int stop)
{
	if(now>m)return;
	
	if(mp.count(now))mp[now]=min(mp[now],step);
	else mp[now]=step;
	
	for(int i=x;i<=stop;++i)
	{
		dfs1(i+1,step+1,now+a[i]/2,stop);
		dfs1(i+1,step,now+a[i],stop);
	}
}

void dfs2(int x,int step,ll now,int stop)
{
	if(now>m||step>=ans)	return;
	
	if(mp.count(m-now))ans=min(ans,step+mp[m-now]);
	
	for(int i=x;i<=stop;++i)
	{
		dfs2(i+1,step+1,now+a[i]/2,stop);
		dfs2(i+1,step,now+a[i],stop);
	}
}

int main()
{
	cin>>n>>m;
	m*=2;
		
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		a[i]*=2;
	}
	
	sort(a+1,a+1+n);
	
	dfs1(1,0,0,n/2);
	dfs2(n/2+1,0,0,n);
	
	cout<<(ans==114514?-1:ans);
	return 0;
}
