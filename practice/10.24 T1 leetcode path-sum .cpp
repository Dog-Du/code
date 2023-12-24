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

    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==nullptr)return false;
        if(root->left==nullptr&&root->right==nullptr)
        {
            if(targetSum-root->val==0)return true;
            else return false;
        }

        return hasPathSum(root->left,targetSum-root->val)||
            hasPathSum(root->right,targetSum-root->val);
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
