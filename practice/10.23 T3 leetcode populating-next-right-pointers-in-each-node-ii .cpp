#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <list>

#define ll long long

using namespace std;


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if(root==nullptr)return root;

        Node*cur=root,*temp=new Node;

        //思路：新建一个头节点，题目意思相当于是把每一层都穿成链表
        //cur用来走当前层，pre用来走下一层给cur铺路，
        //一层走完之后,cur开始走下一层，显然第一个节点就是temp的首节点

        while(cur!=nullptr)
        {
            temp->next=nullptr;

            Node*pre=temp;//it指向头结点，pre指向下一层节点

            while(cur!=nullptr)
            {
                if(cur->left!=nullptr)
                    pre->next=cur->left,pre=pre->next;
                if(cur->right!=nullptr)
                    pre->next=cur->right,pre=pre->next;
                
                cur=cur->next;
            }

            cur=temp->next;
        }

        //delete temp;
        
        return root;
    }
};

class Solution {
public:
    Node* connect(Node* root) {
        if(root==nullptr)return root;

        queue<Node*> que;
        que.push(root);

        while(!que.empty())
        {
            int len=que.size();
            Node* j;

            while(len--)
            {
                j=que.front();
                que.pop();

                if(!que.empty())
                    j->next=que.front();

                if(j->left!=nullptr)
                    que.push(j->left);
                if(j->right!=nullptr)
                    que.push(j->right);
            }

            j->next=nullptr;
        }

        return root;
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
