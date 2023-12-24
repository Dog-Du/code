using namespace std;
#include<iostream>
#include<set>
#include<queue>

const int maxn=1e4+10;

struct node{
	int x,y,time;
};


 
queue<node> que;

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int ans=0;
bool used[maxn][maxn];

int main()
{
	que.push({0+maxn/2,0+maxn/2,0})	;
	que.push({2020+maxn/2,11+maxn/2,0});
	que.push({11+maxn/2,14+maxn/2,0});
	que.push({2000+maxn/2,2000+maxn/2,0});
	
	node j;
	
	while(!que.empty())
	{
		j=que.front();
		que.pop();
		
		
		if(j.time==2020)
		{
			break;
		}
		
		
		for(int nx,ny,i=0;i<4;++i)	
		{
			nx=j.x+dx[i],ny=j.y+dy[i];
			
			if(used[nx][ny])continue;
			
			used[nx][ny]=1;//不知道为什么放在这里会快很多 
			++ans;
			que.push({nx,ny,j.time+1});
		}
	}
	
	cout<<ans;
	return 0;
}
