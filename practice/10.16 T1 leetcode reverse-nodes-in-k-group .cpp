#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;


  struct ListNode {
     int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}

  };

void show(ListNode p)
{
    
}

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int t=k,len=0;
        ListNode*pre=NULL,*p=head,*back=p->next,*P=new ListNode;

        P->next=head;

        while(p)
        {
            p=p->next;
            ++len;
        }

        p=head,pre=P;

        while(len>=k)
        {
            ListNode*temp=pre;
            t=k;

            while(t--)
            {
                back=p->next;
                p->next=pre;
                pre=p;
                p=back;
            }

            if(temp->next)
                temp->next->next=p;

            swap(temp->next,pre);

            len-=k;
        }

        head=P->next;
        
        //free(P);

        return head;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    ListNode*p=new ListNode,*temp=p;
    p->next=NULL;

    int n;
    cin>>n;

    while(n--)
    {
        int x;
        cin>>x;
        temp->next=new ListNode(x);
        temp=temp->next;
        temp->next=NULL;
    }

    p=p->next;

    temp=p;
    while(temp)
    {
        cout<<temp->val<<' ';
        temp=temp->next;
    }
    cout<<endl;

    Solution one;
    p=one.reverseKGroup(p,3);
    
    temp=p;

    while(temp)
    {
        cout<<temp->val<<' ';
        temp=temp->next;
    }


    cout<<endl;
    system("pause");
    return 0;
}
