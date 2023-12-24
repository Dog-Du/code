using namespace std;
#include<iostream>
#define ll long long

//���仯����������,��Ϊ���仯����Ҫ������ѡ��������dp���Ӷ�Ӧ����һ�µ�
//����dp�п���ֱ�Ӽ�֦ 
 
const int maxn=5e5+10;
int n,k;
int f[maxn],a[maxn];

int dfs(int x,int now)
{
	if(f[x])return f[x];
	
	if(x>n)return now;
	
	int ans=0;
	
	for(int i=x;i<=n;++i)
	{
		ans=max(ans,dfs(i+k+1,now+a[i]));
	}
	
	return f[x]=ans;
}

int main()
{
	cin>>n>>k;
	
	for(int i=1,v;i<=n;++i)
	{
		cin>>a[i];
	}

	cout<<dfs(1,0);
	return 0;
}


//
//const int maxn=5e5+10;
//int n,k,ans=0;
//int f[maxn];
//
//int main()
//{
//	cin>>n>>k;
//	
//	for(int i=1,v;i<=n;++i)
//	{
//		cin>>v;
//		f[i]=max(f[i-1],v);
//		if(i-k-1>=0)f[i]=max(f[i],f[i-1-k]+v);
//	}
//
//		
//	cout<<f[n];
//	return 0;
//}
