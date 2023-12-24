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
    void dfs(TreeNode*&root,int nowdeppth,int &maxdepth,vector<int>&ans)
    {
        if(root==nullptr)return;
        
        if(maxdepth==nowdeppth)
            ans.push_back(root->val);
        
        maxdepth=max(maxdepth,++nowdeppth);

        dfs(root->right,nowdeppth,maxdepth,ans);
        dfs(root->left,nowdeppth,maxdepth,ans);
    }

    vector<int> rightSideView(TreeNode* root) {
        int maxdepth=0;

        vector<int> ans;
        dfs(root,0,maxdepth,ans);
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
