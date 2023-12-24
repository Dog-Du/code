#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

#define ll long long

using namespace std;

struct node
{
    char ch;
    node *l, *r;
    node *prior, *next;
    int bf;
    node(char CH)
    {
        l = r = NULL;
        ch = CH;
    }
};

const int maxn = 1e5 + 10;

char ch[maxn];
int len;

void convert(node *&root, string &str)
{
    str.push_back(root->ch);

    if (root->l && root->r)
    {
        str.push_back('(');
        convert(root->l, str);
        str.push_back(',');
        convert(root->r, str);
        str.push_back(')');
    }
    else if (root->l)
    {
        str.push_back('(');
        convert(root->l, str);
        str.push_back(',');
        str.push_back(')');
    }
    else if (root->r)
    {
        str.push_back('(');
        str.push_back(',');
        convert(root->r, str);
        str.push_back(')');
    }
    else
        return;

    return;
}

// 非递归写法，确实反而比递归写法更加简单而且容易理解
void another_answer(node *&root, string &ch)
{
    int len = ch.size();
    if (len == 0) // 特判
    {
        root = NULL;
        return;
    }

    int n = 0; // n用来迭代字符串
    stack<node *> st;

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

void dfs(node *&root, int &p)
{
    // 如果遇见逗号有两种情况，一个是左边是( 另一个是左边是字母
    // 如果是括号，说明后边有字母，不应该再加，把这个逗号留给上一层处理，不然会漏掉字母

    if (ch[p] == ',')
        return;
    else if (ch[p] == ')' || p >= len)
    {
        ++p;
        return;
    }
    else
    {
        root = new node(ch[p++]);

        if (ch[p] == '(')
        {
            dfs(root->l, ++p);

            if (ch[p] == ',')
                ++p;
            // 如果直接++p或者直接p
            //++p 可能会导致 (,C) 在返回时p指向C，导致漏过C
            // p 可能会导致 D(B,C) 在返回时p指向逗号，而后面还有一个字母，导致直接返回，漏掉字母

            dfs(root->r, p);
        }
        else // 如果字母后面是，或者) 直接返回上一层，统一处理
        {
            ++p;
            return;
        }
    }
}

void preshow(node *&root)
{
    if (root == NULL)
        return;
    else
    {
        cout << root->ch << ":" << root->bf << endl;
        preshow(root->l);
        preshow(root->r);
    }
}

void midshow(node *&root)
{
    if (root == NULL)
        return;
    else
    {
        midshow(root->l);
        cout << root->ch << ":" << root->bf << endl;
        midshow(root->r);
    }
}
