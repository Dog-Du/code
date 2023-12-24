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
 
//二分查找
class Solution {
public:
    
    int getdepth(TreeNode*root)
    {
        int depth=0;

        while(root!=nullptr)
            root=root->left,++depth;

        return move(depth);
    }

    bool check(int x,TreeNode*root,int depth)
    {
        //把引索当做编号，0向左，1向右
        while(depth>=0)
        {
            if((x>>depth)&1)
                root=root->right;
            else
                root=root->left;
            
            --depth;
        }

        return root!=nullptr;
    }

    int countNodes(TreeNode* root) {
        if(root==nullptr||root->left==nullptr)return 0;

        int depth=getdepth(root),ans=(1<<(depth-1))-1;
        int l=0,r=(1<<(depth-1))-1,mid,t=0;
        //最多有 (1<<(depth-1))-1 个 即最大的1在 depth-2那里，所以下面check的时候需要传参depth-2
        
        while(l<=r)
        {
            mid=l+r>>1;

            if(check(mid,root,depth-1-1))
                l=mid+1,t=mid;
            else
                r=mid-1;
        }

        return ans+t+1;
    }
};

//基于深度
class Solution {
public:
    //时间复杂度 : O(logn*logn)
    int countNodes(TreeNode* root) {
        if(root==nullptr)return 0;

        int ans=1;
        TreeNode*l=root->left,*r=root->right;
        int depthl=0,depthr=0;
        TreeNode*p1=l,*p2=r;


        while(l!=nullptr||r!=nullptr)//只有有一个不为空就遍历
        {
           depthl=depthr=0;
           p1=l,p2=r;

            //统计左右子树深度
            while(p1!=nullptr)
                p1=p1->left,++depthl;
            
            while(p2!=nullptr)
                p2=p2->left,++depthr;
            
            //左子树深度大于右子树，则右子树是满二叉树，然后在对左子树进行同样操作
            if(depthl>depthr)
            {
                ans+=(1<<depthr); // 应该是 ans+=(1<<depthr)-1 + 1；前半部分是满二叉树节点个数，+1是进入另一个子树之后的
                r=l->right,l=l->left;
            }
            else//否则两者相等，左子树为满二叉树,再对右子树进行同样操作
            {
                ans+=(1<<depthl);
                l=r->left,r=r->right;
            }
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
