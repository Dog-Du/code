using namespace std;
#include<iostream>
#define ll long long

int main()
{
	for(ll x=2020;;++x)
	{
		for(ll y=x+1;x*x-2019*2019>=y*y-x*x;++y)
		{
			if(x*x*2==2019*2019+y*y)
			{
				printf("%lld %lld %lld\n",x,y,x+y);
			}
		}
	}
	return 0;
}
