using namespace std;
#include<iostream>
#include<string>
#define ll long long

//��Ϊһ������û��̫��λ��������dfs����
 
string num;
int a,b;
ll ans=0;

void dfs(int x,ll now)
{
	if(x>=num.size())	
	{
		ans=max(ans,now);
		return;
	}
	
	int t=num[x]-'0';
	int c=min(a,9-t);
	
	a-=c;
	
	dfs(x+1,now*10+t+c);
	
	a+=c;
	
	if(b>t)
	{
		b-=t+1;
		
		dfs(x+1,now*10+9);
		
		b+=t+1;
	}
}

int main()
{
	cin>>num>>a>>b;
	
	dfs(0,0);
	
	cout<<ans;
	return 0;
}


//
//
////̰��˼�룺���ü��������������üӷ���������ȱ��
////���磺99990000 a=0 b=40,����Ȼ����֮������ȷ��
// 
//int main()
//{
//	cin>>n>>a>>b;
//	
//	for(int i=0;i<n.size();++i)
//	{
//		int t=n[i]-'0';
//		
//		if(b>t)
//		{
//			b-=t+1;
//			n[i]='9';
//			continue;
//		}
//		
//		int c=min(a,9-t);
//		
//		a-=c;
//		
//		n[i]=t+c+'0';
//	}
//	
//	cout<<n;
//	
//	return 0;
// } 
