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
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> graph[numCourses],top;
        int ind[numCourses]={0};
        
        for(auto&iter:prerequisites)
        {
            ++ind[iter.front()];
            graph[iter.back()].push_back(iter.front());
        }

        for(int i=0;i<numCourses;++i)
            if(ind[i]==0)top.push_back(i);
        
        int p=0;

        while(p<top.size())
        {
            for(auto&to:graph[top[p]])
            {
                if(--ind[to]==0)top.push_back(to);
            }

            ++p;
        }

        return top.size()==numCourses;
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
