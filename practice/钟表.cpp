using namespace std;
#include<iostream> 
#define ll long long

int main()
{
	int cnt=1;
	
	while(cnt<=6*3600)
	{
		double a=360.0*(cnt%60)/60;
		double b=360.0*(cnt%3600)/3600;
		double c=360.0*(cnt%(3600*12))/(3600*12);
		
		double A=abs(c-b);
		double B=abs(b-a);
		A=min(A,360-A);
		B=min(B,360-B);
		
		if(A==2*B)
		{
			printf("%d %d %d\n",cnt/3600,cnt/60%60,cnt%60);
		}
		++cnt;
	}
	return 0;
}
