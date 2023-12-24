using namespace std;
#include<iostream>
#include<cstring>

int ans=0,n;

char ch[5005];

bool check(int l,int r)
{
	while(l<r)
	{
		if(ch[r]<ch[l])return true;
		else if(ch[r--]>ch[l++])return false;
	}
	return false;
}

int main()
{
	cin>>ch+1;
	
	n=strlen(ch+1);
	
	for(int i=1;i<=n;++i)
	{
		for(int j=i+1;j<=n;++j)
		{
			if(check(i,j))++ans;
		}
	}
	
	cout<<ans;
	return 0;
}
