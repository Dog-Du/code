using namespace std;
#include<iostream>
#include<cstring>
#define ll long long

int n,ans=0;

ll f[505][500];

ll dfs(int x,int now,int pre)
{
	if(f[now][pre]!=-1)return f[now][pre];
	
	if(now==0&&x>=2)return f[now][pre]=1;
	
	ll ans=0;
	
	for(int i=pre+1;i<=now;++i)	
	{
		ans+=dfs(x+1,now-i,i);
	}
	
	return f[now][pre]=ans;
}

int main()
{
	cin>>n;	
	
	memset(f,-1,sizeof f);
	cout<<dfs(0,n,0);
	
//	cout<<ans;
	return 0;
}
