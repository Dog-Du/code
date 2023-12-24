using namespace std;
#include<iostream>

const int maxn=1e5+10;

int n;
int a[maxn],add[maxn];
long long ans=0;

int main()
{
	cin>>n;
	
	for(int i=1;i<=n;++i)	cin>>a[i];
	
	for(int i=0,cnt1,cnt0;i<=20;++i)
	{
		cnt1=cnt0=0;
		
		for(int j=1;j<=n;++j)
			add[j]=add[j-1]^(a[j]>>i&1);
			
		for(int j=0;j<=n;++j)
			if(add[j])++cnt1;
			else ++cnt0;
		
		ans+=(1ll<<i)*cnt0*cnt1;
	}
	
	cout<<ans;
	return 0;
}
