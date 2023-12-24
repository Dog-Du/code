#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==nullptr)return {};

        vector<vector<int>> ans;
        vector<int> t;
        queue<TreeNode*> que;

        que.push(root);

        while(!que.empty())
        {
            int len=que.size();
            t.clear();

            while(len--)
            {
                TreeNode*j=que.front();

                t.push_back(j->val);

                if(j->left!=nullptr)que.push(j->left);
                if(j->right!=nullptr)que.push(j->right);

                que.pop();
            }

            ans.push_back(t);
        }

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
