#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//100 -> 111 100 101 110 111
//想法是：如果一位想要被&上，那么right-left就不能大于1<<i不然会有数字让其为零
//同时两个端点也需要相等，这样能保证答案正确。
//答案：实际上就是公共01前缀

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int dis=right-left,ans=0;

        for(int i=0;i<32;++i)
            if((left>>i&1)&&(right>>i&1)&&dis<(1<<i))
                ans|=(1<<i);
            
        return ans;
    }
};

//公共前缀的方法。
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int i=0;
        while(left>>i!=right>>i)
            ++i;
        return (left>>i)<<i;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
