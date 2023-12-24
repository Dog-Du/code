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
 

class BSTIterator {
public:
    vector<TreeNode*> vec;//只用来保存左子树指针
    TreeNode*p;//迭代

    BSTIterator(TreeNode* root) {
        p=root;
    }
    
    int next() {
        while(p!=nullptr)//肯定在最左边，并一路保存左子树节点
        {
            vec.push_back(p);
            p=p->left;
        }

        p=vec.back();
        vec.pop_back();

        int ret=p->val;
        p=p->right;

        return ret;
    }
    
    bool hasNext() {
        return p!=nullptr||!vec.empty();
    }
};

class BSTIterator {
public:

    struct node{
        TreeNode*tree;
        node*next;

        node():tree(nullptr),next(nullptr){}
    }*it,*temp;

    void dfs(TreeNode*root)
    {
        if(root==nullptr)return;

        dfs(root->left);
        
        temp->next=new node;
        temp->next->tree=root;
        temp=temp->next;

        dfs(root->right);
    }

    BSTIterator(TreeNode* root) {
        it=new node;
        temp=it;
        dfs(root);
    }
    
    int next() {
        it=it->next;
        return it->tree->val;
    }
    
    bool hasNext() {
        return it->next!=nullptr;
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
