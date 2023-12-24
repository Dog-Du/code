using namespace std;
#include<iostream>
#define ll long long

const int N=20210605;
int prime[N+1];
bool is_prime[N+1];
int ans=0,tot=0;

bool check(int x)
{
	int t;
	
	while(x)
	{
		t=x%10;
		if(t!=2&&t!=3&&t!=5&&t!=7)return false;
		x/=10;
	}
	
	return true;
}
int main()
{
	for(int i=2;i<=N;++i)
	{
		if(!is_prime[i])
		{
			if(check(i))++ans;
			prime[++tot]=i;
		}
		
		for(int j=1;prime[j]*i<=N;++j)
		{
			is_prime[prime[j]*i] =1;
			
			if(i%prime[j]==0)break;
		}
	}
	
	cout<<ans;
	return 0;
}
