using namespace std;
#include<iostream>

const int maxn=1e6+10;

int n,m;

struct node{
	int sum,ma,mi;
	bool flag;
}t[maxn<<2];

void pushup(node&x,node&l,node&r)
{
	x.sum=l.sum+r.sum;
	x.ma=max(l.ma,l.sum+r.ma);
	x.mi=min(l.mi,l.sum+r.mi);
	return;
}

void reverse(node&x)
{
	x.sum*=-1;
	x.ma*=-1;
	x.mi*=-1;
	x.flag^=1;
	swap(x.ma,x.mi);
	return;
}

void pushdown(int x)
{
	if(t[x].flag)
	{
		reverse(t[x<<1]);
		reverse(t[x<<1|1]);
		t[x].flag=0;
	}
}

void build(int x,int l,int r)
{
	if(l==r)
	{
		char ch;
		
		cin>>ch;
		
		if(ch=='(')t[x].sum=1;
		else t[x].sum=-1;
		
		t[x].ma=t[x].mi=t[x].sum;
		
		return;
	}
	
	int mid=l+r>>1;
	
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	
	pushup(t[x],t[x<<1],t[x<<1|1]);
}

void modify(int x,int l,int r,int L,int R)
{
	if(l>=L&&r<=R)	
	{
		reverse(t[x]);
		return;
	}
	
	int mid=l+r>>1;
	
	pushdown(x);
	
	if(mid>=L)modify(x<<1,l,mid,L,R);
	if(mid<R)modify(x<<1|1,mid+1,r,L,R);
	
	pushup(t[x],t[x<<1],t[x<<1|1]);
}

node query(int x,int l,int r,int L,int R)
{
	if(l>=L&&r<=R)return t[x];
	
	int mid=l+r>>1;
	node ans={0,-maxn,maxn,0},t1=ans,t2=ans;
	
	pushdown(x);
	
	if(mid>=L)t1=query(x<<1,l,mid,L,R);
	if(mid<R)t2=query(x<<1|1,mid+1,r,L,R);
	
	pushup(ans,t1,t2);
	
	return ans;
}


int get(int x)
{
	int l=x,r=n,mid,ans=x,pos=0;
	
	while(l<=r)
	{
		mid=l+r>>1;
		
		if(query(1,1,n,x,mid).mi>=0)
		{
			pos=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	
	l=x,r=pos;
	
	node t1,t2;
	
	while(l<=r)
	{
		mid=l+r>>1;
		
		t1=query(1,1,n,x,mid);
		t2={0,0,0,0};
		
		if(mid+1<=pos)t2=query(1,1,n,mid+1,pos);
		
		if(t1.sum==0||t1.sum+t2.mi==0)
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	
	if(ans==x)return 0;
	return ans;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	
	build(1,1,n);
	
	int op,x,y;
	
	while(m--)
	{
		cin>>op;
		
		if(op==1)	
		{
			cin>>x>>y;
			modify(1,1,n,x,y);
		}
		else
		{
			cin>>x;
			cout<<get(x)<<'\n';
		}
	}
	return 0;
}
