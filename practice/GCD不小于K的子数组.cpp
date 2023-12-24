using namespace std;
#include<iostream>
#define ll long long

const int maxn=2e5+10;

ll a[maxn],t[maxn<<2];
ll k,ans=0;
int n;

ll __gcd(ll a,ll b)
{
	return b==0?a:__gcd(b,a%b)	;
}

void build(int x,int l,int r)
{
	if(l==r) 
	{
		t[x]=a[l];
		return ;
	}
	
	int mid=l+r>>1;
	
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	
	t[x]=__gcd(t[x<<1],t[x<<1|1]);
}

ll query(int x,int l,int r,int L,int R)
{
	if(l>=L&&r<=R)	return t[x];
	
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
	
	cin>>n>>k;
	
	for(int i=1;i<=n;++i)cin>>a[i];
	
	build(1,1,n);
	
	for(int i=1,l,r,mid,t;i<=n;++i)
	{
		l=i,r=n,t=i-1;

		while(l<=r)
		{
			mid=l+r>>1;
			
			if(query(1,1,n,i,mid)>=k)
			{
				l=mid+1;
				t=mid;
			}
			else
				r=mid-1;
		}
		
		ans+=t-i+1;
	}
	
	cout<<ans;
	
	return 0;
}
