using namespace std;
#include<iostream>

int ans=0;

int used[10][10];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
 
void dfs(int x,int y)
{
	if(x==0||y==7)
	{
		++ans;
		return;
	}
	
	for(int i=0,nx,ny;i<4;++i)
	{
		nx=x+dx[i],ny=y+dy[i];
		
		if(nx<0||nx>7||ny<0||ny>7||used[nx][ny]||nx==ny)continue;
		
		used[nx][ny]=used[ny][nx]=1;
		
		dfs(nx,ny);
		
		used[nx][ny]=used[ny][nx]=0;
	}
}
int main()
{
	for(int i=0;i<=7;++i)
		dfs(i,i);
	
	cout<<ans;	
	return 0;
}
