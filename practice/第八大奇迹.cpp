using namespace std;
#include<iostream>

const int maxn=1e5+10;

struct node{
	int v[8]={0};
}t[maxn<<2];//ÿ���ڵ��¼��������ǰ�˴� 

inline void pushup(node & x,node & l,node & r)//�ù鲢����˼��ϲ� 
{
	int p1=0,p2=0,p=0;
	
	while(p<8&&p1<8&&p2<8)
		if(l.v[p1]>r.v[p2])x.v[p++]=l.v[p1++];
		else x.v[p++]=r.v[p2++];	
}

inline void modify(int x,int l,int r,int &dist ,int &v)
{
	if(l==r)
	{
		t[x].v[0]=v;
		return;
	}
	
	int mid=l+r>>1;
	
	if(mid>=dist)modify(x<<1,l,mid,dist,v);
	else modify(x<<1|1,mid+1,r,dist,v);
	
	pushup(t[x],t[x<<1],t[x<<1|1]);
}

inline node query(int x,int l,int r,int &L,int &R)
{
	if(l>=L&&r<=R)return t[x];
	
	int mid=l+r>>1;
	node t1,t2,ans;
	
	if(mid>=L)t1=query(x<<1,l,mid,L,R);
	if(mid<R)t2=query(x<<1|1,mid+1,r,L,R);
	
	pushup(ans,t1,t2);
	
	return ans;
}

int l,n,x,y;
char op;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>l>>n;
	
	while(n--)
	{
		cin>>op>>x>>y;
		
		if(op=='C')modify(1,1,l,x,y);
		else cout<<query(1,1,l,x,y).v[7]<<'\n';
	}
	return 0;
}
//���ȶ��� 
//using namespace std;
//#include<iostream>
//#include<queue>
//#define IT priority_queue<int,vector<int>,greater<int>>
//
//const int maxn=1e5+10;
//
//IT t[maxn<<2];
//
//inline void pushup(IT &x,IT& l,IT&r)
//{
//	while(!x.empty())x.pop();
//	
//	IT it=l;
//	
//	while(!it.empty())
//	{
//		x.push(it.top());
//		it.pop();
//	}
//	
//	it=r;
//	
//	while(!it.empty())
//	{
//		x.push(it.top());
//		it.pop();
//	}
//	
//	while(x.size()>8)x.pop();
//}
//
//inline void modify(int x,int l,int r,int & dist,int &v)
//{
//	if(l==r)
//	{
//		while(!t[x].empty())t[x].pop();
//		
//		t[x].push(v);
//		return;
//	}
//	
//	int mid=l+r>>1;
//	
//	if(mid>=dist)modify(x<<1,l,mid,dist,v);
//	else modify(x<<1|1,mid+1,r,dist,v);
//	
//	pushup(t[x],t[x<<1],t[x<<1|1]);
//}
//
//inline IT query(int x,int l,int r,int& L,int &R)
//{
//	if(l>=L&&r<=R)
//	{
//		return t[x];
//	}
//	
//	int mid=l+r>>1;
//	
//	IT ans,t1,t2;
//	
//	if(mid>=L)t1=query(x<<1,l,mid,L,R);
//	if(mid<R)t2=query(x<<1|1,mid+1,r,L,R);
//	
//	pushup(ans,t1,t2);
//	
//	return ans;
//}
//
//int l,n,x,y;
//char op;
//
//
//int main()
//{
//	ios::sync_with_stdio(false);
//	cin.tie(0),cout.tie(0);
//	
//	cin>>l>>n;
//	
//	while(n--)
//	{
//		cin>>op>>x>>y;
//		
//		if(op=='C')
//		{
//			modify(1,1,l,x,y);
//		}
//		else
//		{
//			IT it=query(1,1,l,x,y);
//			
//			if(it.size()<8)cout<<0<<'\n';
//			else cout<<it.top()<<'\n'; 
//		}
//	}
//	return 0;
//}
