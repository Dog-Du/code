#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;


//  Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
private:
    static const int N=1e5+10;
    int sum[N]={0};

    void dfs(TreeNode* root,int depth=0)
    {
        if(root==nullptr)return;

        sum[depth]+=root->val;
        dfs(root->left,depth+1);
        dfs(root->right,depth+1);
    }

    void dfs2(TreeNode*root,int depth=0)
    {
        int s=(root->left==nullptr?0:root->left->val)+
            (root->right==nullptr?0:root->right->val);
        
        if(root->left!=nullptr)
        {
            root->left->val=sum[depth+1]-s;
            dfs2(root->left,depth+1);
        }

        if(root->right!=nullptr)
        {
            root->right->val=sum[depth+1]-s;
            dfs2(root->right,depth+1);
        }
    }

public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        dfs(root);
        dfs2(root);
        root->val=0;
        return root;   
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
