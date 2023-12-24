// #include <iostream>
// #include <string>

// using namespace std;

// // 用后序遍历和中序遍历求原来的二叉树，同时输出前序遍历

// struct node
// {
//     int x;
//     node *l, *r;

//     node(int CH)
//     {
//         l = NULL, r = NULL;
//         x = CH;
//     }
// };

// const int maxn = 1e5 + 10;

// int mid[maxn], rear[maxn];

// int search(int l, int r, int p)
// {
//     for (int i = l; i <= r; ++i)
//     {
//         if (mid[i] == rear[p])
//             return i;
//     }

//     return -1;
// }

// void dfs(node *&root, int l, int r, int &p)
// {
//     if (l > r)
//     {
//         ++p;
//         return;
//     }

//     if (l == r)
//     {
//         root = new node(rear[p]);
//         return;
//     }
//     else
//     {
//         int j = search(l, r, p);

//         root = new node(rear[p]);

//         dfs(root->r, j + 1, r, --p);

//         dfs(root->l, l, j - 1, --p);
//     }
// }

// void show(node *root)
// {
//     if (!root)
//         return;
//     else
//     {
//         cout << root->x << ' ';
//         show(root->l);
//         show(root->r);
//     }
// }

// int main()
// {
//     int n, temp;

//     cin >> n;

//     for (int i = 1; i <= n; ++i)
//         cin >> mid[i];

//     for (int i = 1; i <= n; ++i)
//         cin >> rear[i];

//     node *root;

//     temp = n;

//     dfs(root, 1, n, temp);

//     show(root);

//     cout << endl;
//     system("pause");
//     return 0;
// }