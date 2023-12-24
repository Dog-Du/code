#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>


#define ll long long

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        vector<int> res(n,1);

        //当相等的时候不进行操作

        //从左向右看，比左边大必须加+1
        for(int i=1;i<n;++i)
            if(ratings[i]>ratings[i-1])
                res[i]=res[i-1]+1;
        

        //从右向左看，比右边大必须加+1，但同时也要满足比左边大+1，所以取max
        for(int i=n-2;i>=0;--i)
            if(ratings[i]>ratings[i+1])
                res[i]=max(res[i+1]+1,res[i]);
        
        return accumulate(res.begin(),res.end(),0);
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
