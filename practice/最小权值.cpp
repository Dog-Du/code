using namespace std;
#include<iostream>
#define ll long long

ll f[3000];

ll dfs(int x)
{
	if(f[x]!=-1)	return f[x];
	
	if(x==0)return 0;
	
	ll ans=1e17;
	
	for(int i=0;i<x;++i)
	{
		ans=min(ans,1+2*dfs(i)+3*dfs(x-i-1)+i*i*(x-i-1));
	}
	
	return f[x]=ans;
}

int main()
{
	for(int i=0;i<3000;++i)f[i]=-1;
	
	cout<<dfs(2021);
	return 0;
}
