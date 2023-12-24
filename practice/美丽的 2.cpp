using namespace std;
#include<iostream>

int ans=0;

bool check(int x)
{
	while(x)	
	{
		if(x%10==2)return true;
		x/=10;
	}
	
	return false;
}

int main()
{
	for(int i=1;i<=2020;++i)
		if(check(i))++ans;
		
	cout<<ans;
	return 0;
}
