using namespace std;
#include<iostream>
#define ll long long

//����һ�������� X �����Ա�ʾ�����ɸ������˻�����ʽ��
//�� X = p1��1 ? p2��2 ���� ? pk��k
//Լ������ = (a1 + 1)(a2 + 1)����(ak + 1)

int p[200];
bool prime[200];

int main()
{
	
	for(int i=3;i<=100;++i)	
	{
		for(int j=2;j*j<=i;++j)
		{
			if(i%j==0)prime[i]=1;
		}
	}
	
	for(int i=1;i<=100;++i)
	{
		for(int j=2;j<=i;++j)
		{
			int k=i;
			while(!prime[j]&&k%j==0)
			{
				p[j]++;
				k/=j;
			}
		}
	}
	
	ll ans=1;
	
	for(int i=2;i<=100;++i)
		if(p[i])ans*=(p[i]+1);
		
	cout<<ans;
	return 0;
}
