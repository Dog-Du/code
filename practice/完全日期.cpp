using namespace std;
#include<iostream>
#include<cmath>
#define ll long long

int mon[]={0,31,28,31,30,31,30,31,31,30,31,30,31} ;
int ans=0;

int func(int x)
{
	int t=0;
	
	while(x)
		t+=x%10,x/=10;
	
	return t;
}

bool check(int x)
{
	int t=sqrt(x)	;
	return x==t*t;
}

int main()
{
	for(int year=2001;year<=2021;++year)	
	{
		if(year%400==0||(year%4==0&&year%100!=0))
			mon[2]=29;
		else 
			mon[2]=28;
		
		for(int month=1;month<=12;++month)
		{
			for(int day=1;day<=mon[month];++day)
			{
				if(check(func(year)+func(day)+func(month)))
					++ans;
			}
		}
	}
	
	cout<<ans;
	return 0;
}
