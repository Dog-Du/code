using namespace std;
#include<iostream>
#define ll long long

const int maxn=2e5+10;

//运用性质：a+b>=a^b 肯定成立，因为a^b可能增大可能减小 
ll a[maxn],add[maxn],bdd[maxn];
ll ans=0;
int n;

int main()
{
	cin>>n;
	
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		add[i]=add[i-1]+a[i];
		bdd[i]=bdd[i-1]^a[i];
	}
	
	
	for(int i=1,l,r,mid,t;i<=n;++i)
	{
		l=i,r=n;
		
		while(l<=r)
		{
			mid=l+r>>1;
			
			if((add[mid]-add[i-1])<=(bdd[mid]^bdd[i-1]))
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
