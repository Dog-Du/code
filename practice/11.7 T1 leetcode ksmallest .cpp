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

//和洛谷的一样的做法
class Solution {
public:

    int getsize(TreeNode*&root)
    {
        if(root==nullptr)return 0;
        return getsize(root->left)+getsize(root->right)+1;
    }

    int kthSmallest(TreeNode* root, int k) {
        int l=getsize(root->left);
        if(k==l+1)return root->val;
        else if(k<=l)return kthSmallest(root->left,k);
        else if(k>l+1)return kthSmallest(root->right,k-l-1);
    }
};

//中序遍历找啊找，找到第k个
class Solution {
public:
    int p,ans;

    void dfs(TreeNode*&root)
    {
        if(root==nullptr)return;
        dfs(root->left);
        if(--p==0)
        {
            ans=root->val;
            return;
        }
        dfs(root->right);
    }

    int kthSmallest(TreeNode* root, int k) {
        p=k;
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
