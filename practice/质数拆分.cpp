using namespace std;
#include<iostream>
#define ll long long

bool is_prime[3000];
int prime[3000];
int tot=0;
ll f[3000];

void prime_fliter()
{
	for(int i=2;i<=2019;++i)
	{
		if(!is_prime[i])prime[++tot]=i;
		
		for(int j=1;prime[j]*i<=2019;++j)
		{
			is_prime[prime[j]*i]=1;
			
			if(i%prime[j]==0)break;
		}
	}	
}

int main()
{
	prime_fliter();
	
	f[0]=1;
	
	for(int i=1;i<=tot;++i)
	{
		for(int j=2019;j>=prime[i];--j)
			f[j]+=f[j-prime[i]];
	}
	
	cout<<f[2019];
	return 0;
}
