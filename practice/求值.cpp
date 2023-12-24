using namespace std;
#include<iostream>

int main()
{
	for(int i=5;;++i)
	{
		int cnt=0;
		
		for(int j=1;j*j<=i;++j)
		{
			if(i%j==0)
			{
				if(j*j!=i)++cnt;
				++cnt;
			}
		}
		
		if(cnt==100)
		{
			cout<<i;
			break;
		}
	}
	return 0;
}
