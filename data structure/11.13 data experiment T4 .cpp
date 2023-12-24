#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct node
{
    node *l, *r;
    node *prior, *next;
    char ch;
    node(char CH) : l(nullptr), r(nullptr), prior(nullptr), next(nullptr), ch(CH) {}
};

void CreateTreeByBigList(node *&root, string &ch)
{
    int len = ch.size();
    if (len == 0) // 特判
    {
        root = NULL;
        return;
    }

    int n = 0; // n用来迭代字符串

    stack<node *> st; // 借助stl的一个栈

    node *p = root;        // p指针用来迭代
    p = new node(ch[n++]); // 同时让n指向下一个

    // st.push(root);//不要直接push进去

    while (n < len)
    {

        if (ch[n] == '(') // 如果有(，保存本地，进入下一层(先左边)
        {
            st.push(p);
            p = p->l;
        }
        else if (ch[n] == ',') // 如果有逗号，显然是左边的结束了，进行上一层的右边
        {
            st.top()->l = p; // 保存左边的信息
            p = st.top();
            // st.pop(); //不要pop，因为上一层还有用
            p = p->r;
        }
        else if (ch[n] == ')') // 如果是) ，说明这一层结束了
        {
            st.top()->r = p; // 保存后边
            p = st.top();    // 返回上一层
            st.pop();        // pop这一层
        }
        else
        {
            p = new node(ch[n]); // 是字母，建立新节点
        }

        ++n;
    }

    root = p; // 修改，因为是引用型参数
}

void DestoryTree(node *&root)
{
    if (root == nullptr)
        return;
    DestoryTree(root->l);
    DestoryTree(root->r);
    delete root;
    root = nullptr;
}

void GetPrior(node *root, node *&pre)
{
    if (root == nullptr)
        return;

    GetPrior(root->l, pre);
    root->prior = pre;
    pre = root;
    GetPrior(root->r, pre);
}

void GetNext(node *root, node *&next)
{
    if (root == nullptr)
        return;

    GetNext(root->r, next);
    root->next = next;
    next = root;
    GetNext(root->l, next);
}

void CreateBinaryTree(node *&root, string &s)
{
    CreateTreeByBigList(root, s);

    node *temp = nullptr;
    GetPrior(root, temp);
    temp = nullptr;
    GetNext(root, temp);
}

void ShowPreOrder(node *root)
{
    while (root->prior != nullptr)
        root = root->prior;

    while (root != nullptr)
    {
        cout << root->ch << ' ';
        root = root->next;
    }
}

void ShowRearOrder(node *root)
{
    while (root->next != nullptr)
        root = root->next;

    while (root != nullptr)
    {
        cout << root->ch << ' ';
        root = root->prior;
    }
}

void solve()
{
    string s;
    cin >> s;

    // 创建一个中序的全线索二叉树
    node *root;

    CreateBinaryTree(root, s);

    ShowPreOrder(root);
    cout << endl;

    ShowRearOrder(root);
    cout << endl;

    DestoryTree(root);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cout << "input test times" << endl;
    cin >> t;

    while (t--)
    {
        solve();
    }

    cout << endl;
    system("pause");
    return 0;
}
