using namespace std;
#include<iostream>
#include<cstring>

char s[1005],t[1005];
int dp[1005][1005];
int n,m;

int main()
{
	cin>>s+1>>t+1;
	
	n=strlen(s+1);
	m=strlen(t+1);

	for(int i=1;i<=m;++i)
		dp[0][i]=2000;
	
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(s[i]==t[j])dp[i][j]=dp[i-1][j-1];
			else
				dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]);
		}
	}
	
	cout<<dp[n][m];
	return 0;
}
