#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define ll long long

using namespace std;

class Solution {
private:
    int n;

    void getnext(string&s,vector<string> &bank,vector<int>&vec)
    {
        for(int i=0,cnt;i<n;++i)
        {
            if(bank[i]=="Q")continue;
            cnt=0;
            for(int j=0;j<8;++j)
                if(s[j]!=bank[i][j])++cnt;
            
            if(cnt==1)vec.push_back(i);
        }
    }

public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        queue<pair<string,int>> que;
        que.push({startGene,0});
        n=bank.size();
        vector<int> vec;
        pair<string,int> j;

        while(!que.empty())
        {
            j=que.front();
            que.pop();
            vec.clear();

            getnext(j.first,bank,vec);

            for(auto&it:vec)
            {
                if(bank[it]==endGene)return j.second+1;
                que.push({bank[it],j.second+1});
                bank[it]="Q";
            }
        }

        return -1;
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
