#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//贪心，因为题目已经保证只有一个答案，在sum>=0的前提下，只要找到在前面的路径上cur>0的即可
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        int cur=0,sum=0,ans=0,length=gas.size();

        for(int i=0;i<length;++i)
        {
            sum+=gas[i]-cost[i];
            cur+=gas[i]-cost[i];

            if(cur<0)
            {
                cur=0;
                ans=i+1;

            }
        }

        if(sum<0)return -1;
        return ans;
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
