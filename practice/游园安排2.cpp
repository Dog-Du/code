using namespace std;
#include<iostream>
#include<string>

const int maxn=1e6+10;

string s,name[maxn],ans;

char ch;
int size=0,tot=0,p=0;
int dp[maxn],res[maxn];

int main()
{
	while(cin>>ch)
	{
		if(ch>='A'&&ch<='Z')
		{
			name[tot++]=s;
			s.clear();
		}
		s.push_back(ch);
	}
	name[tot]=s;
	
	for(int i=1,l,r,mid,t;i<=tot;++i)
	{
		if(name[i]>name[dp[size]])
		{
			dp[++size]=i;
			res[++p]=size;
			continue;
		}
			
		l=1,r=size;
		
		while(l<=r)
		{
			mid=l+r>>1;
			
			
			if(name[i]<=name[dp[mid]])
			{
				t=mid;
				r=mid-1;
			}
			else
				l=mid+1;
		}
		
		dp[t]=i;
		res[++p]=t;
	}
	
	while(size>0)
	{
		if(size==res[p])
		{
			ans=name[p]+ans;
			--size;
		}
		
		--p;
	}
	
	cout<<ans;
	return 0;
}
