#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//可以使用O(n+m）的空间复杂度（设置两个标记行和列的数组）
//也可以把数组的第一行第一列当做上述中的标记数组，然后对第一行第一列进行特别处理就好了

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n=matrix.size(),m=matrix.front().size();
        bool row=0,col=0;

        for(int i=0;i<n;++i)
            if(!matrix[i][0])
            {
                row=1;
                break;
            }

        for(int i=0;i<m;++i)
            if(!matrix[0][i])
            {
                col=1;
                break;
            }

        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                if(!matrix[i][j])
                    matrix[i][0]=matrix[0][j]=0;
        
        for(int i=1;i<n;++i)    
            if(!matrix[i][0])
                for(int j=0;j<m;++j)
                    matrix[i][j]=0;
        
        for(int j=1;j<m;++j)
            if(!matrix[0][j])
                for(int i=0;i<n;++i)
                    matrix[i][j]=0;
        
        if(row)for(int i=0;i<n;++i)matrix[i][0]=0;
        if(col)for(int i=0;i<m;++i)matrix[0][i]=0;

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
