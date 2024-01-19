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
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int n=s1.size(),m=s2.size();
        int p1=0,p2=0;
        int cnt1=0,cnt2=0;

        while(cnt1<n1)
        {
            if(s1[p1]==s2[p2])
                ++p1,++p2;
            else 
                ++p1;
            
            if(p1==n&&p2==m)//正好一起到达尾端
            {
                ++cnt1,++cnt2;
                break;
            }
            else if(p1==n&&p2==0)//p1到达尾端，而p2这时还没开始
            {
                ++cnt1;
                break;
            }
            else if(p1==n)
                ++cnt1,p1=0;
            else if(p2==m)
                ++cnt2,p2=0;
        }

        //在n1下存在 s1的倍数 使得 s2 能够正好取整，这时可以使用公式
        if((p1==n&&p2==m)||(p1==n&&p2==0))       
            return (n1*cnt2)/(n2*cnt1);

        //不然需要遍历整个 s1*n1 的长度，这个时候cnt2表示在 s1*n1 下 s2出现的次数
        //那么除以n2就是答案。
        return cnt2/n2;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    Solution one;
    string s1="bacaba",s2="abacab";
    one.getMaxRepetitions(s1,3,s2,1);

    cout<<endl;
    system("pause");
    return 0;
}
