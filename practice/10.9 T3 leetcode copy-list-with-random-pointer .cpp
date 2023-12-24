#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>

#define ll long long

using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        //利用哈希表，把拷贝的和原来的进行映射
        unordered_map<Node*,Node*> mp;

        Node*p=head;

        while(p)
        {
            mp[p]=new Node(p->val);
            p=p->next;
        }

        p=head;

        while(p)
        {
            mp[p]->next=mp[p->next];
            mp[p]->random=mp[p->random];

            p=p->next;
        }

        return mp[head];
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        //把新的节点放在原来的节点的后面，这样
        //p->next->random=p->random->next
        
        if(!head)return NULL;

        Node*p=head,*temp,*ans;

        while(p)
        {
            temp=p->next;
            p->next=new Node(p->val);
            
            p->next->next=temp;
            p=temp;
        }

        p=head;
        ans=head->next;

        
        while(p)
        {
            if(p->random)
                p->next->random=p->random->next;
            else
                p->next->random=NULL;
            p=p->next->next;
        }

        p=head,temp=head->next;

        while(p&&temp)
        {
            Node*P=temp->next;

            p->next=P;

            if(P)
                temp->next=P->next;

            p=P;
            temp=temp->next;
        }

        return ans;
    }
};

//我的，垃圾至极的O(n^2)解法，居然过了，这晒LeetCode数据真小。
class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return NULL;

        Node *ans = new Node(0), *p = ans, *temp = head;

        while (temp)
        {
            p->val = temp->val;

            if (temp->next)
            {
                p->next = new Node(0);
                p = p->next;
            }

            temp = temp->next;
        }

        p->next = NULL;

        temp = head;
        p = ans;

        while (temp)
        {
            Node *p1 = ans, *p2 = head;

            while (p1 && p2)
            {
                if (p2 == temp->random)
                {
                    p->random = p1;
                    break;
                }

                p1 = p1->next;
                p2 = p2->next;
            }

            temp = temp->next;
            p = p->next;
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cout << endl;
    system("pause");
    return 0;
}
