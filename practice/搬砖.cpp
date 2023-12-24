using namespace std;
#include<iostream>
#include<algorithm>
#define ll long long

const int maxn=1e3+10;
struct node{
	ll w,v;
	bool operator<(node&it)const
	{
		return w+v<it.w+it.v;
	}
}t[maxn];

ll f[maxn*30];
ll ans=0;
int n;

int main()
{
	cin>>n;
	
	for(int i=1;i<=n;++i)cin>>t[i].w>>t[i].v;
	
	sort(t+1,t+1+n);
	
	for(int i=1;i<=n;++i)
	{
		for(int j=min(t[i].w+t[i].v,(ll)40000);j>=t[i].w;--j)
		{
			f[j]=max(f[j],f[j-t[i].w]+t[i].v);
			ans=max(ans,f[j]);
		}
	}
	
	cout<<ans;
	return 0;
}
