using namespace std;
#include<iostream>
#define ll long long

const int maxn=3e2+10;

ll f[maxn][maxn][maxn];
int prime[maxn];

int n,m,w,r,c,h,tot=0,mod=1e9+7;
int dx[]={1,0,0};
int dy[]={0,1,0};
int dz[]={0,0,1};

bool check(int x)
{
	for(int i=2;i*i<=x;++i)	
		if(x%i==0)return false;
	return true;
}

ll dfs(int x,int y,int z)
{
	if(f[x][y][z]!=-1)return f[x][y][z];
	
	if(x==n&&y==m&&z==w)return 1;
	
	ll ans=0;
	
	for(int i=1,step;i<=tot;++i)
	{
		step=prime[i];
		
		if(x+step<=n)ans=(ans+dfs(x+step,y,z))%mod;
		if(y+step<=m)ans=(ans+dfs(x,y+step,z))%mod;
		if(z+step<=w)ans=(ans+dfs(x,y,z+step))%mod;
	}
	
	return f[x][y][z]=ans;
}

int main()
{
	
	cin>>n>>m>>w;
	
	for(int i=1;i<=n;++i)	
		for(int j=1;j<=m;++j)
			for(int k=1;k<=w;++k)
				f[i][j][k]=-1;
				
	cin>>r>>c>>h;
	
	f[r][c][h]=0;
	
	cin>>r>>c>>h;
	
	f[r][c][h]=0;
	
	for(int i=2;i<=maxn-10;++i)
	{
		if(check(i))prime[++tot]=i;
	}
	
	cout<<dfs(1,1,1);
	return 0;
}
