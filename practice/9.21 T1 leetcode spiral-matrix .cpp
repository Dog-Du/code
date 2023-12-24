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
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        if(matrix.size()==0)return ans;

        //上下左右边界
        int top=0,bottom=matrix.size()-1,l=0,r=matrix.front().size()-1;

        while(1)
        {
            for(int i=l;i<=r;++i)
                ans.push_back(matrix[top][i]);
            if(++top>bottom)break;

            for(int i=top;i<=bottom;++i)
                ans.push_back(matrix[i][r]);
            if(--r<l)break;

            for(int i=r;i>=l;--i)
                ans.push_back(matrix[bottom][i]);
            if(--bottom<top)break;

            for(int i=bottom;i>=top;--i)
                ans.push_back(matrix[i][l]);
            if(++l>r)break;
        }

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
