using namespace std;
#include<iostream>
#include<iostream>

string s1="ABC",s2="AEF",s3="CKA",s4="DEB",s5="BDK";

bool check(char a,char b,char c)
{
	//条件一
	char ch[]={a,b,c};
	
	int cnt=0;
	
	for(int i=0;i<3;++i)
		if(ch[i]==s1[i])++cnt;
		
	if(cnt!=1)return false;
	
	//条件二 
	cnt=0;
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j) 	
			if(ch[i]==s2[j]&&i!=j)++cnt;
	}
	
	if(cnt!=1)return false;
	
	//条件三	
	cnt=0;
	
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
			if(ch[i]==s3[j]&&i!=j)++cnt;
	}
	
	if(cnt!=2)return false;
	
	//条件四 
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
			if(ch[i]==s4[j])return false;
	}
	
	cnt=0;
	
	//条件五 
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
			if(ch[i]==s5[j]&&i!=j)++cnt;
	}
	
	if(cnt!=1)return false;
	
	return true;
}
int main()
{
	for(char a='A';a<='K';++a)
	{
		for(char b='A';b<='K';++b)
		{
			for(char c='A';c<='K';++c)
			{
				if(check(a,b,c))
				{
					cout<<a<<b<<c<<endl;
				}
			}
		}
	}
	return 0;
}
