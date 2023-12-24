#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

#define ll long long

using namespace std;

 struct TreeNode {
      char val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  class Solution {
public:
    TreeNode*pre=nullptr;

    void flatten(TreeNode* root) {
       
       //过程就是，把右子树剖下给左子树中最靠右的节点的右子树，然后把左子树置空
       while(root!=nullptr)
       {
            if(root->left==nullptr)//如果左子树为空，那么已经符合条件，进行下一次循环
                root=root->right;
            else
            {
                TreeNode*pre=root->left;//寻找左子树中最靠右的节点，它的下一个节点是root的右子树

                while(pre->right!=nullptr)
                    pre=pre->right;
                
                //这是pre指向的就是左子树中最靠右的节点
                pre->right=root->right;//它的下一个节点就是右子树
                root->right=root->left;//本身的下一个节点是本身的左子树
                root->left=nullptr;//左边置空

                root=root->right;//前往下一个
            }
       }
    }
};

void preshow(TreeNode *&root)
{
    if (root == NULL)
        return;
    else
    {
        cout << root->val;
        preshow(root->left);
        preshow(root->right);
    }
}

string ch;
int len;

void another_answer(TreeNode *&root)
{
    if (len == 0) // 特判
    {
        root = NULL;
        return;
    }

    int n = 0; // n用来迭代字符串
    stack<TreeNode *> st;

    TreeNode *p = root;        // p指针用来迭代
    p = new TreeNode(ch[n++]); // 同时让n指向下一个

    // st.push(root);//不要直接push进去

    while (n < len)
    {

        if (ch[n] == '(') // 如果有(，保存本地，进入下一层(先左边)
        {
            st.push(p);
            p = p->left;
        }
        else if (ch[n] == ',') // 如果有逗号，显然是左边的结束了，进行上一层的右边
        {
            st.top()->left = p; // 保存左边的信息
            p = st.top();
            // st.pop(); //不要pop，因为上一层还有用
            p = p->right;
        }
        else if (ch[n] == ')') // 如果是) ，说明这一层结束了
        {
            st.top()->right = p; // 保存后边
            p = st.top();    // 返回上一层
            st.pop();        // pop这一层
        }
        else
        {
            p = new TreeNode(ch[n]); // 是字母，建立新节点
        }

        ++n;
    }

    root = p; // 修改，因为是引用型参数
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    TreeNode*root;

    cin>>ch;
    len=ch.size();

    another_answer(root);
    Solution one;

    one.flatten(root);

    preshow(root);

    cout<<endl;
    system("pause");
    return 0;
}
