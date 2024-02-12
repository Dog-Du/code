#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define ll long long

using namespace std;

//对于 a0,a1,a2,a3,a4...an-1 假设a0最后变成了x
//那么序列变成 x,x+1,x+2,....,x+n-1
//操作次数为： |a0-x| + |a1-x-1| +....+ |a(n-1)-x-(n-1)|
//令 bi=ai-i
//操作次数为： |b0-x| + |b1-x| + ... + |b(n-1)-x|
//显然，这个值在最小的时候，x为 bn 序列的中位数。-> 有一个定理
//如何求操作次数？
//假设 b0 ... b(n-1) 是从低到高排序，x为其中一个中位数
//我们考虑 b(n-1)和b0这两个数字的操作次数
// 即： b(n-1) - x + x - b0 = b(n-1) - b0 与 x 无关
//所以以此类推。
//如果n为偶数：那么上面的两两相减可以完美进行，即分成两块，数字之和相减
//如果n为奇数：中间的数字为中位数，那么答案为 中位数右边数字之和 减去 中位数左边数字之和。
//维护动态流的中位数和左右两个堆的和即可。

class Solution {
private:
    priority_queue<int,vector<int>,greater<int>> pright;//小根堆
    priority_queue<int,vector<int>,less<int>> pleft;//大根堆
    //不再设置mid，把mid当成pright的top
    //如果pright.size()==pleft.size()，则为偶数，有两个中位数
    //如果pright.size()==pleft.size()+1，那么中位数就是pright.size(),
    //也就是说两个堆的大小只有两个关系：
    //pright.size()==pleft.size() 或者 pright.size()==pleft.size()+1

    static const long long MOD=1'000'000'007;
    long long left=0,right=0;//记录两个堆的和

    void push(int x)
    {
        if(pright.empty()||x>=pright.top())        
        {
            pright.push(x);
            right+=x;
        }
        else
        {
            pleft.push(x);
            left+=x;
        }

        //大小进行调整。
        if(pright.size()>pleft.size()+1)
        {
            pleft.push(pright.top());
            left+=pright.top();
            right-=pright.top();
            pright.pop();
        }
        else if(pleft.size()>pright.size())
        {
            pright.push(pleft.top());
            right+=pleft.top();
            left-=pleft.top();
            pleft.pop();
        }
    }

public:
    vector<int> numsGame(vector<int>& nums) {
        int n=nums.size();
        vector<int> ans(n);

        for(int i=0;i<n;++i)
        {
            int b=nums[i]-i;

            push(b);

            ans[i]=(right-left-(i%2==0?pright.top():0))%MOD;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
