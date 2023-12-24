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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ans;

        queue<TreeNode*> que;
        que.push(root);
        ll len,sum;
        TreeNode*j;

        while(!que.empty())
        {
            len=que.size();
            sum=0;

            for(int i=0;i<len;++i)
            {
                j=que.front();
                sum+=j->val;

                if(j->left!=nullptr)que.push(j->left);
                if(j->right!=nullptr)que.push(j->right);
                que.pop();
            }

            ans.push_back(sum*1.0/len);
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
