#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 


class Solution {
public:
    
    int ans=-9999999;//全局变量记录每一个 包含本节点与左右子树值的和的值 的最大值，返回的是 包含节点或者不包含的 两者的最大值 不用再传递子树中的最大值，因为这个被ans记录

    int dfs(TreeNode*root)//
    {
        if(root==nullptr)return 0;

        int l=dfs(root->left),r=dfs(root->right);
        ans=max(l+r+root->val,ans);

        return max(max(l,r)+root->val,0);
    }

    int maxPathSum(TreeNode* root) {
        dfs(root);
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
