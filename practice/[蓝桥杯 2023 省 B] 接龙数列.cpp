using namespace std;
#include<iostream>
#define ll long long

int dp[20];
int n,ans;
string s;

int main()
{
	cin>>n;
	
	for(int i=1;i<=n;++i)
	{
		cin>>s;
		
		//dp[i]表示以前几个数字以i结尾的最大A接龙序列
		//如果相等,则可以转化成dp[首]+1 或者 dp[尾] 取最大值
		//如果不相等，则只能转化成，dp[尾] 
		 
		dp[s.back()-'0']=max(dp[s.back()-'0'],dp[s.front()-'0']+1);
		
		ans=max(ans,dp[s.back()-'0']);
	
	}
	
	cout<<n-ans;
	return 0;
}
