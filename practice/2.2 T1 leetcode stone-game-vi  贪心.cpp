#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

// 贪心做法：
// 证明：
// 假设只有两个石头,对于 a， b 的价值分别是 a1, a2, b1, b2

// 第一种方案是A取第一个，B取第二个，A与B的价值差是 c1 = a1 - b2
// 第二种方案是A取第二个，B取第一个，A与B的价值差是 c2 = a2 - b1
// 那么这两种方案对于A来说哪一种更优，就取决于两个方案的价值差的比较

// 记 c = c1 - c2 = （a1 - b2） - (a2 - b1) = (a1 + b1) - (a2 + b2)

// 如果c > 0 那么方案一更优，如果c == 0，那么两种方案价值一样，如果c < 0那么方案二更优

// 那么比较两个方案的优劣 == 比较 a1 + b1 与 a2 + b2 的优劣 ，
// 归纳一下就是比较每个下标 i 的 a[i] + b[i] 的优劣

// 所以贪心的策略：将两组石头的价值合并，每次取价值最大的那一组。

///PS:贪心想不出来就想基本情况（只有两个的情况），然后再推式子

// 提供一个同一思路的不同解释。

// 可以定义一个效用函数f， f[i] = aliceValues[i] + bobValues[i]

// 为什么这样定义？

// 因为某人（比如Alice）任取一个，她不仅能自己得aliceValues[i] 分，还能让Bob少得bobValues[i] 分。 相当于取这个值就产生了aliceValues[i] + bobValues[i]的效果 。

// 我们按照效用值逆序排序，效用值越高就应当越先取。

class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int cur1=0,cur2=0,n=aliceValues.size();
        vector<pair<int,int>> vec(n);

        for(int i=0;i<n;++i)
        {
            vec[i]={aliceValues[i]+bobValues[i],i};
        }

        sort(vec.begin(),vec.end());
        reverse(vec.begin(),vec.end());

        for(bool flag=true;const auto&it:vec)
        {
            if(flag)
                cur1+=aliceValues[it.second];
            else 
                cur2+=bobValues[it.second];
            
            flag=!flag;
        }

        if(cur1>cur2)
            return 1;
        else if(cur1<cur2)
            return -1;
        else
            return 0;
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
