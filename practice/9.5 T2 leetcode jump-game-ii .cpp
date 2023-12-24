#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//动态规划暴力解决，勉强能过，数据再大一些就必须用线段树优化才能过了
//这里实现了线段树。因为这道题只需要单点查询，所以没有使用tag，需要注意的是pushup里面是max

class Solution {
public:

    static const int maxn=1e4+10;
    int t[maxn<<2];

    void pushup(int x)
    {
        t[x]=max(t[x<<1],t[x<<1|1]);
    }

    void pushdown(int x)
    {
        t[x<<1]=min(t[x<<1],t[x]);
        t[x<<1|1]=min(t[x<<1|1],t[x]);
    }

    void build(int x,int l,int r)
    {
        t[x]=1e9;

        if(l==r)
        {
            if(l==0)t[x]=0;
            else
                t[x]=1e9;
            return;
        }

        int mid=l+r>>1;

        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);

        pushup(x);
    }

    void modify(int x,int l,int r,int L,int R,int k)
    {
        if(l>=L&&r<=R)
        {
            t[x]=min(t[x],k);
            return;
        }

        pushdown(x);
        
        int mid=l+r>>1;

        if(mid>=L)modify(x<<1,l,mid,L,R,k);
        if(mid<R)modify(x<<1|1,mid+1,r,L,R,k);

        pushup(x);
    }

    int query(int x,int l,int r,int dist)//单点查询，不需要tag标记
    {
        if(l==r)return t[x];
        int mid=l+r>>1;

        pushdown(x);

        if(mid>=dist)return query(x<<1,l,mid,dist);
        else return query(x<<1|1,mid+1,r,dist);
    }

    int jump(vector<int>& nums) {
        int length=nums.size();
      //  vector<int> dp(length+1,(int)1e5+10);

        build(1,0,length-1);

        for(int i=0;i<length;++i)
        {
            modify(1,0,length-1,i,i+nums[i],query(1,0,length-1,i)+1);

            // for(int i=0;i<length;++i)
            //     cout<<query(1,0,length-1,i)<<' ';
            // cout<<endl;
        }

        return query(1,0,length-1,length-1);
    }
};

// class Solution {
// public:
//     int jump(vector<int>& nums) {

//         int length=nums.size(),cover=0,cnt=0,next=0;

//         if(length<=1)return 0;

//         for(int i=0;i<=cover;++i)
//         {
//             next=max(next,nums[i]+i);

//             if(i==cover)
//             {
//                 ++cnt;
//                 cover=next;

//                 if(cover>=length-1)return cnt;
//             }
//         }

//         return cnt;
//     }
// };

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<int> vec={2,3,0,1,4};

    cout<<one.jump(vec);


    cout<<endl;
    system("pause");
    return 0;
}
