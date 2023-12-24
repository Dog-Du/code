using namespace std;
#include<iostream>

int ans=0;
int used[10][10];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

void dfs(int x,int y,int step)
{
	if(step>12)return;
	
	if(x==1&&y==1&&step>2)
	{
		++ans;
		return;
	}
	
	for(int i=0,nx,ny;i<4;++i)
	{
		nx=x+dx[i],ny=y+dy[i];
		
		if(nx<1||nx>6||ny<1||ny>6||used[nx][ny])continue;
		
		used[nx][ny]=1;
		
		dfs(nx,ny,step+1);
		
		used[nx][ny]=0;
	}
}
int main()
{
	dfs(1,1,0);
	
	cout<<ans; 
	return 0;
}
