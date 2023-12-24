using namespace std;
#include<iostream>
#include<algorithm>
#include<unordered_map>
#define ll long long

const int maxn=1e5+10;

ll n,a,b,p[maxn];

unordered_map<ll,bool> A,B,C;

int main()
{
	cin>>n>>a>>b;
	
	for(int i=1;i<=n;++i)
	{
		cin>>p[i];
		C[p[i]]=1;
	}
	
	
	for(int i=1;i<=n;++i)
	{
		if(C[p[i]]==0)continue;
		
		if(C[a-p[i]]||A[a-p[i]])
		{
			A[a-p[i]]=1;
			A[p[i]]=1;
			C[a-p[i]]=0;
			C[p[i]]=0;
		}
		else if(C[b-p[i]]||B[b-p[i]])
		{
			B[b-p[i]]=1;
			B[p[i]]=1;
			C[b-p[i]]=0;
			C[p[i]]=0;
		}
		else
			{
				cout<<"NO";
				return 0;
			}
	}
	
	cout<<"YES\n";
	
	for(int i=1;i<=n;++i)
		if(A[p[i]])cout<<"0 ";
		else cout<<"1 ";
	return 0;
}
