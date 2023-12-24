using namespace std;
#include<iostream>
#define ll long long

//任意一个正整数 X 都可以表示成若干个质数乘积的形式，
//即 X = p1α1 ? p2α2 …… ? pkαk
//约数个数 = (a1 + 1)(a2 + 1)……(ak + 1)

int p[200];
bool prime[200];

int main()
{
	
	for(int i=3;i<=100;++i)	
	{
		for(int j=2;j*j<=i;++j)
		{
			if(i%j==0)prime[i]=1;
		}
	}
	
	for(int i=1;i<=100;++i)
	{
		for(int j=2;j<=i;++j)
		{
			int k=i;
			while(!prime[j]&&k%j==0)
			{
				p[j]++;
				k/=j;
			}
		}
	}
	
	ll ans=1;
	
	for(int i=2;i<=100;++i)
		if(p[i])ans*=(p[i]+1);
		
	cout<<ans;
	return 0;
}
