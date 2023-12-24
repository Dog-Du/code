using namespace std;
#include<iostream>
#include<algorithm>

const int maxn=1e6+10;

int tot=0,prime[maxn],f[maxn];
bool is_prime[maxn];

void prime_fliter()
{
	for(int i=2;i<=maxn-10;++i)	
	{
	//	f[i]=f[i-1];
		
		if(!is_prime[i])
		{
			prime[++tot]=i;
		//	++f[i];
		}
		
		for(int j=1;prime[j]*i<=maxn-10;++j)
		{
			is_prime[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
	
	for(int i=2;i<=maxn-10;++i)
		if(!is_prime[i])f[i]=f[i-1]+1;
		else f[i] =f[i-1];
}

int a,b,k,L,R;

bool check(int mid)
{
	for(int i=a;i+mid-1<=b;++i)
		if(f[i+mid-1]-f[i-1]<k)return false;
		
	return true;
}

int main()
{
	
	prime_fliter();
	
	cin>>a>>b>>k;
	
	int l=0,r=b-a+1,mid,ans=-1;
	
	while(l<=r)
	{
		mid=l+r>>1;
		
		if(check(mid))
		{
			ans=mid;
			r=mid-1;	
		}
		else
			l=mid+1;
	}
	
	cout<<ans;
	return 0;
}
