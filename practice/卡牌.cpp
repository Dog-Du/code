using namespace std;
#include<iostream>
#define ll long long

const int maxn=2e5+10;

struct node{
	ll a,b;
}t[maxn];

ll n,m;

bool check(ll x)
{
	ll temp=m;
	
	for(int i=1;i<=n;++i)	
	{
		if(t[i].a+t[i].b<x)return false;
		if(t[i].a>=x)continue;
		
		temp-=x-t[i].a;
		
		if(temp<0)return false;
	}
	
	return true;
}

int main()
{
	cin>>n>>m;
	
	for(int i=1;i<=n;++i)cin>>t[i].a;
	for(int i=1;i<=n;++i)cin>>t[i].b;
	
	ll l=0,r=maxn<<2,mid,ans;
	
	while(l<=r)
	{
		mid=l+r>>1;
		
		if(check(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else
			r=mid-1;
	}
	
	cout<<ans;
	return 0;
}
