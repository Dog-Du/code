using namespace std;
#include<iostream>
#define ll long long

const int maxn=1e5+10;

int n,cnt=0;
ll t[maxn<<2];

inline ll __gcd(ll a,ll b)
{
	return b==0?a:__gcd(b,a%b);
}

void build(int x,int l,int r)
{
	if(l==r)
	{
		cin>>t[x];
		
		if(t[x]==1)++cnt;
		return;	
	}	
	
	int mid=l+r>>1;
	
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	
	t[x]=__gcd(t[x<<1],t[x<<1|1]);
	return;
}

inline ll query(int x,int l,int r,int L,int R)
{
	if(l>=L&&r<=R)return t[x];
	
	int mid=l+r>>1;
	ll ans=0;
	
	if(mid>=L)ans=__gcd(query(x<<1,l,mid,L,R),ans);
	if(mid<R)ans=__gcd(query(x<<1|1,mid+1,r,L,R),ans);
	
	return ans;	
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n;
	
	build(1,1,n);
	
	if(cnt)
	{
		cout<<n-cnt;
		return 0;
	}
	
	if(query(1,1,n,1,n)!=1)
	{
		cout<<-1;
		return 0;
	}
	
	int ans=1e9;
	
	for(int i=1,l,r,mid;i<=n;++i)
	{
		l=i,r=n;
		
		while(l<=r)
		{
			mid=l+r>>1;
			
			if(query(1,1,n,i,mid)==1)
			{
				r=mid-1;
				ans=min(ans,mid-i+1);
			}
			else
				l=mid+1;
		}
	}
	
	cout<<n+ans-2;
	return 0;
}
