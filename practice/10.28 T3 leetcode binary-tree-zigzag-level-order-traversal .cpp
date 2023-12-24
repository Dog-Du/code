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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root==nullptr)return {};

        vector<vector<int>> ans;
        vector<int> t;
        vector<TreeNode*> ou,ji;

        ou.push_back(root);
        int cnt=0;

        while(!ou.empty()||!ji.empty())
        {
            TreeNode*j;
            t.clear();
            
            if(cnt%2==0)
            {
                while(!ou.empty())
                {
                    j=ou.back();

                    t.push_back(j->val);

                    if(j->left!=nullptr)ji.push_back(j->left);
                    if(j->right!=nullptr)ji.push_back(j->right);

                    ou.pop_back();
                }
            }
            else
            {
                while(!ji.empty())
                {
                    j=ji.back();

                    t.push_back(j->val);

                    if(j->right!=nullptr)ou.push_back(j->right);
                    if(j->left!=nullptr)ou.push_back(j->left);

                    ji.pop_back();
                }
            }

            ans.push_back(t);
            ++cnt;
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
