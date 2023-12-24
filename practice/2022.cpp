using namespace std;
#include<iostream>
#define ll long long

ll f[3000][20];

int main()
{
	f[0][0]=1;
	
	for(int i=1;i<=2022;++i)
	{
		for(int j=10;j>=1;--j)
			for(int k=2022;k>=i;--k)
				f[k][j]+=f[k-i][j-1];
	}
	
	cout<<f[2022][10];
	return 0;
}
