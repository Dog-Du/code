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
	
	for(int i=1;i<=tlen;++i)dp[0][i]=10000;//��ʼ���� 
	
	for(int i=1;i<=slen;++i)
	{
		for(int j=1;j<=tlen;++j)
		{
			if(s[i]==t[j])dp[i][j]=dp[i-1][j-1];//�����Ȳ��ò��� 
			else
				dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]);//�������������ѡ���޸ĺ�ɾ�����޸���Ҫ+1��ɾ������Ҫ+1����Ϊ������ 
		}
	}
	
	cout<<dp[slen][tlen];
	return 0;
}
