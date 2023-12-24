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
 
//检查中序遍历的前驱是不是大于等于本身就好了，这是bst的定义
class Solution {
public:
    ll pre=INT64_MIN;

    bool isValidBST(TreeNode* root) {
        if(root==nullptr)return true;

        if(!isValidBST(root->left))return false;
        if(root->val<=pre)return false;
        pre=root->val;
        return isValidBST(root->right);
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
