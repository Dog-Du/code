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
    int trap(vector<int>& height) {
        int n=height.size(),ans=0;
        vector<int> lmax(n,-1),rmax(n,-1);

        lmax.front()=height.front();
        rmax.back()=height.back();

        for(int i=1;i<n;++i)    
            lmax[i]=max(lmax[i-1],height[i]);

        for(int i=n-2;i>=0;--i)
            rmax[i]=max(rmax[i+1],height[i]);
        
        for(int i=1,t;i<n-1;++i)
        {
            t=min(lmax[i-1],rmax[i+1])-height[i];

            if(t>0)ans+=t;
        }

        return ans;
    }
};

// 其实还可以从每个格子上进行考虑。比如对于一个格子我们寻找右边最大的，
//在寻找左边最大的格子，然后取最小值，之后再减去本身就是这个格子贡献的水量。 
//当然，如果我们用两个指针去探测最大值最小值时间复杂度肯定是O(n^2)这是不可接受的。
//于是我们想到了线段树，剩下的就很简单了。


class Solution {
public:

    static const int maxn=2e4+10;
    int t[maxn<<2];

    void build(int x,int l,int r,vector<int> & vec)
    {
        if(l==r)
        {
            t[x]=vec[l];
            return;
        }

        int mid=l+r>>1;

        build(x<<1,l,mid,vec);
        build(x<<1|1,mid+1,r,vec);

        t[x]=max(t[x<<1],t[x<<1|1]);
    }

    int query(int x,int l,int r,int L,int R)
    {
        if(l>=L&&r<=R)return t[x];

        int mid=l+r>>1,ans=-1;

        if(mid>=L)ans=max(ans,query(x<<1,l,mid,L,R));
        if(mid<R)ans=max(ans,query(x<<1|1,mid+1,r,L,R));

        return ans;
    }

    int trap(vector<int>& height) {
        int n=height.size(),ans=0;
        build(1,0,n-1,height);

        for(int i=1,t;i<n-1;++i)
        {
            t=min(query(1,0,n-1,0,i-1),query(1,0,n-1,i+1,n-1))-height[i];
            if(t>0)ans+=t;
        }

        return ans;
    }
};


//两次单调栈,从整体的角度进行考虑
class Solution {
public:

    int trap(vector<int>& height) {
        int ans=0,n=height.size();
        vector<int> st,rear(n,-1),front(n,-1),add(n);

        //前缀和加速，就算没有add速度也很快
        add[0]=height[0];

        for(int i=1;i<n;++i)
            add[i]=add[i-1]+height[i];

        //单调栈填rear
        for(int i=0;i<n;++i)
        {
            while(!st.empty()&&height[st.back()]<=height[i])
            {
                rear[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }

        st.clear();

        //单调栈填front
        for(int i=n-1;i>=0;--i)
        {
            while(!st.empty()&&height[st.back()]<height[i])//注意这里改成了小于，不然会重复计算格子。这个需要自己思考为什么
            {
                front[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }

        //如果找到最大的格子，直接break
        for(int i=0;i<n;++i)
        {
            if(rear[i]==-1)break;

            ans+=(rear[i]-i-1)*height[i];

            ans-=(add[rear[i]-1]-add[i]);//直接利用前缀和减去这部分

            i=rear[i]-1;//直接跳到后面那一个格子，中间的已经减过了，不需要在遍历了
        }

        //找到最大的格子直接break
        for(int i=n-1;i>=0;--i)
        {
            if(front[i]==-1)break;

            ans+=(i-front[i]-1)*height[i];

            ans-=(add[i-1]-add[front[i]]);

            i=front[i]+1;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<int> vec={4,2,0,3,2,5};

    cout<<one.trap(vec)<<endl;


    cout<<endl;
    system("pause");
    return 0;
}
