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
    void rotate(vector<vector<int>>& matrix) {
        int n=matrix.size();

        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
                swap(matrix[i][j],matrix[j][i]);
                
        int l=0,r=n-1;

        while(l<r)
        {
            for(int i=0;i<n;++i)
                swap(matrix[i][l],matrix[i][r]);
            ++l,--r;
        }
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
