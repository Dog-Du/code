#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;


class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};


class Solution {
private:
    Node*dfs(int left,int right,int top,int bottom,vector<vector<int>>&grid)
    {
        int midx=left+right>>1,midy=top+bottom>>1;

        for(int i=left;i<right;++i)
        {
            for(int j=top;j<bottom;++j)
            {
                if(grid[j][i]!=grid[top][left])
                    return new Node(
                        false,false,
                        dfs(left,midx,top,midy,grid),
                        dfs(midx,right,top,midy,grid),
                        dfs(left,midx,midy,bottom,grid),
                        dfs(midx,right,midy,bottom,grid)
                    );
            }
        }

        return new Node(grid[top][left],1);
    }

public:
    Node* construct(vector<vector<int>>& grid) {
        return dfs(0,grid.size(),0,grid.size(),grid);
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
