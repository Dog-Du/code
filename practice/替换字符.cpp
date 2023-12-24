using namespace std;
#include<iostream>
#include<cstring>
#include<set>
#include<algorithm>
#define IT set<ODT>::iterator


//const int maxn=1e5+10;
//
//int m,len,t[maxn<<2][26];
//char ch[maxn];
//
//void pushdown(int x)
//{
//	for(int i=0;i<26;++i)
//		t[x<<1][i]=t[x][t[x<<1][i]],
//		t[x<<1|1][i]=t[x][t[x<<1|1][i]];
//		
//	
//	for(int i=0;i<26;++i)
//		t[x][i]=i;
//			
//}
//
//void build(int x,int l,int r)
//{
//	for(int i=0;i<26;++i)
//		t[x][i]=i;
//	
//	if(l==r)return;
//	
//	int mid=l+r>>1;
//	
//	build(x<<1,l,mid);
//	build(x<<1|1,mid+1,r);
//		
//}
//
//void modify(int p,int l,int r,int L,int R,int x,int y)
//{
//	if(l>=L&&r<=R)
//	{
//		for(int i=0;i<26;++i)
//			if(t[p][i]==x)t[p][i]=y;
//		
//		return;
//	}
//	
//	int mid=l+r>>1;
//	
//	pushdown(p);
//	
//	if(mid>=L)modify(p<<1,l,mid,L,R,x,y);
//	if(mid<R)modify(p<<1|1,mid+1,r,L,R,x,y);
//	
//}
//
//void print(int x,int l,int r)
//{
//	if(l==r)
//	{
//		putchar(t[x][ch[l]-'a']+'a');
//		return;
//	}	
//	
//	int mid=l+r>>1;
//	
//	pushdown(x);
//	
//	print(x<<1,l,mid);
//	print(x<<1|1,mid+1,r);
//}
//
//int main()
//{
//	cin>>ch+1;
//	len=strlen(ch+1);
//	
//	build(1,1,len);
//	
//	cin>>m;
//	while(m--)
//	{
//		int l,r;
//		char x,y;
//		
//		cin>>l>>r>>x>>y;
//		
//		modify(1,1,len,l,r,x-'a',y-'a');
//	}
//	
//	print(1,1,len);
//	return 0;
//}
