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
		
		//dp[i]��ʾ��ǰ����������i��β�����A��������
		//������,�����ת����dp[��]+1 ���� dp[β] ȡ���ֵ
		//�������ȣ���ֻ��ת���ɣ�dp[β] 
		 
		dp[s.back()-'0']=max(dp[s.back()-'0'],dp[s.front()-'0']+1);
		
		ans=max(ans,dp[s.back()-'0']);
	
	}
	
	cout<<n-ans;
	return 0;
}
