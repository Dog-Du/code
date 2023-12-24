#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

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
    void dfs(TreeNode*&root,vector<int>&preorder,vector<int>&inorder,unordered_map<int,int>&mp,int l,int r,int &p)
    {
        root=new TreeNode(preorder[p]);
        int j=mp[preorder[p]];
        
        if(j+1<=r)dfs(root->right,preorder,inorder,mp,j+1,r,--p);
        if(l<=j-1)dfs(root->left,preorder,inorder,mp,l,j-1,--p);
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& preorder) {
        TreeNode*root;
        int p=preorder.size()-1;
        unordered_map<int,int> mp;

        for(int i=0;i<inorder.size();++i)
            mp[inorder[i]]=i;

        dfs(root,preorder,inorder,mp,0,preorder.size()-1,p);
        return root;
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
