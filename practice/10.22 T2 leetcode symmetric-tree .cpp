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

    bool dfs(TreeNode*l,TreeNode*r)
    {
        if(l==nullptr&&r==nullptr)return true;
        if((l==nullptr)^(r==nullptr))return false;

        return (l->val!=r->val)?false:
            dfs(l->left,r->right)&&dfs(l->right,r->left);
    }

    bool isSymmetric(TreeNode* root) {
        return root==nullptr?true:dfs(root->left,root->right);
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
