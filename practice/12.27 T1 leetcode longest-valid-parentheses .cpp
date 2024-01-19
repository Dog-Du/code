#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    vector<int> t,add;

    void build(int x,int l,int r)
    {
        if(l==r)
        {
            t[x]=add[l];
            return;
        }

        int mid=l+r>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        t[x]=min(t[x<<1],t[x<<1|1]);
    }

    int query(int x,int l,int r,int L,int R)
    {
        if(l>=L&&r<=R)
            return t[x];
        
        int mid=l+r>>1,ans=1e9;

        if(mid>=L)ans=min(ans,query(x<<1,l,mid,L,R));
        if(mid<R)ans=min(ans,query(x<<1|1,mid+1,r,L,R));
        return ans;
    }

    int longestValidParentheses(string s) {
        if(s.size()==0)return 0;

        int n=s.size();
        add.resize(n+1,0);
        t.resize(n<<2);

        for(int i=0;i<n;++i)
        {
            add[i+1]=add[i]+(s[i]==')'?-1:1);
        }

        build(1,1,n);

        int ans=0;

        for(int i=1,l,r,mid,pos,t;i<=n;++i)
        {
            if(s[i-1]==')')continue;

            l=i,r=n,pos=-1;

            while(l<=r)
            {
                mid=l+r>>1;
                if(query(1,1,n,i,mid)>=add[i-1])
                    l=mid+1,pos=mid;
                else
                    r=mid-1;
            }

            l=i,r=pos;
            t=-1;

            while(l<=r)
            {
                mid=l+r>>1;
                if(query(1,1,n,mid,pos)==add[i-1])
                    t=mid,l=mid+1;
                else
                    r=mid-1;
            }

            if(t!=-1&&add[i-1]==add[t])
                ans=max(ans,t-i+1);
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    string s="()()(";
    Solution one;
    one.longestValidParentheses(s);



    cout<<endl;
    system("pause");
    return 0;
}
