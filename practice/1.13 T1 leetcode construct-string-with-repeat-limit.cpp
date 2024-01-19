#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

#define ll long long

using namespace std;

//桶贪心
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        map<char,int,greater<char>> mp;

        for(auto&it:s)
            mp[it]++;
        
        int k;
        decltype(mp.begin()) iter,tmp;

        string ans;

        for(iter=mp.begin();iter!=mp.end();++iter)
        {
            tmp=iter;
            ++tmp;
            k=0;

            while(iter->second>0)
            {
                if(k==repeatLimit)
                {
                    if(tmp!=mp.end())
                    {
                        --tmp->second;
                        ans.push_back(tmp->first);
                        k=0;

                        if(tmp->second==0)
                        {
                            auto x=tmp++;
                            mp.erase(x);
                        }
                    }
                    else
                        return ans;
                }

                --iter->second;
                ++k;
                ans.push_back(iter->first);

            }
        }

        return ans;
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    string ans="robnsdvpuxbapuqgopqvxdrchivlifeepy";
    Solution one;
    cout<<one.repeatLimitedString(ans,2);


    cout<<endl;
    system("pause");
    return 0;
}
