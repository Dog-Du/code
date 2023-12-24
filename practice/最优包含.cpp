using namespace std;
#include<iostream>
#include<cstring>

char s[1005],t[1005];
int dp[2000][2000] = { 0 };
int slen,tlen;
 
int main()
{
	cin>>s+1>>t+1;
	slen=strlen(s+1);
	tlen=strlen(t+1);
	
	for(int i=1;i<=tlen;++i)dp[0][i]=10000;//初始化， 
	
	for(int i=1;i<=slen;++i)
	{
		for(int j=1;j<=tlen;++j)
		{
			if(s[i]==t[j])dp[i][j]=dp[i-1][j-1];//如果相等不用操作 
			else
				dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]);//如果不等有两个选择：修改和删除，修改需要+1，删除不需要+1（因为包含） 
		}
	}
	
	cout<<dp[slen][tlen];
	return 0;
}
