// #include <iostream>
// #include <string>

// using namespace std;

// //用前序遍历和中序遍历求原来的二叉树，同时输出后序遍历

// struct node
// {
//     char ch;
//     node *l, *r;

//     node(char CH)
//     {
//         l = NULL, r = NULL;
//         ch = CH;
//     }
// };

// string mid,front;
// int n;

// void dfs(node*&root,int l,int r,int & p)
// {
//     if(l>r)
//     {
//         --p;

//         //如果到了左边界或者右边界即没有左右孩子的时候这次探入是失败的，应该把p减回去
//         //或者在下面加一个条件判断

//         return;
//     }

//     if(l==r)
//     {
//         root=new node(front[p]);
//         return;
//     }
//     else
//     {
//         int j=mid.find(front[p]);

//         root=new node(front[p]);

//         dfs(root->l,l,j-1,++p);
        
//         dfs(root->r,j+1,r,++p);
//     }
// }

// void show(node * &root)
// {
//     if(!root)return ;

//     show(root->l);
//     show(root->r);

//     cout<<root->ch;
// }

// int main()
// {
//     cin>>mid>>front;
//     n=mid.size();

//     node * root;

//     int p=0;

//     dfs(root,0,n-1,p);

//     show(root);

//     cout << endl;
//     system("pause");
//     return 0;
// }