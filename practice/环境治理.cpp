using namespace std;
#include<iostream>
#define ll long long

const int maxn=1e2+10;
int n,q;
int w[maxn][maxn],t[maxn][maxn],b[maxn][maxn];

bool check(int day)
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			t[i][j]=w[i][j];
	
	for(int i=1;i<=n;++i)
	{
		int val=day/n+(day%n>=i?1:0);
		
		for(int j=1;j<=n;++j)
			t[i][j]-=val,t[j][i]-=val;
	}
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			t[i][j]=max(t[i][j],b[i][j]);
	
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				t[i][j]=min(t[i][j],t[i][k]+t[k][j]);
	
	int clean=0;
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			clean+=t[i][j];
			
	return clean<=q;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>q;
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>w[i][j];
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>b[i][j];
			
	int l=0,r=1e8,mid,ans=-1;
	
	while(l<=r)
	{
		mid=l+r>>1;
		
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}	
		else
		 	l=mid+1;
	} 
	
	cout<<ans;
	return 0;
}
