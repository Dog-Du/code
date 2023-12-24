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
 
class Solution {
private:

    bool empty(ListNode*p)
    {
        return p==nullptr;
    }

    void splice(ListNode*&head,ListNode*&p)
    {
        ListNode*temp=head;
        head=head->next;
        temp->next=p;
        p=temp;
    }

    void merge(ListNode*&list,ListNode*&p)
    {
        ListNode*p1=list,*p2=p,*it=nullptr,*ans=nullptr;

        while(p1!=nullptr&&p2!=nullptr)
        {
            if(p1->val<p2->val)
            {
                if(it==nullptr)it=ans=p1;
                else
                {
                    it->next=p1;
                    it=it->next;
                }
                p1=p1->next;
            }
            else
            {
                if(it==nullptr)it=ans=p2;
                else
                {
                    it->next=p2;
                    it=it->next;
                }
                p2=p2->next;
            }
        }

        if(p1==nullptr)
            (it==nullptr)?ans=p2:it->next=p2;
        else
            (it==nullptr)?ans=p1:it->next=p1;
        
        list=ans;
        p=nullptr;
    }

public:
    ListNode* sortList(ListNode* head) {
        if(head==nullptr||head->next==nullptr)return head;

        ListNode *carry=nullptr;
        ListNode *counter[64];

        for(int i=0;i<64;++i)
            counter[i]=nullptr;
        
        int fill=0;

        while(!empty(head))
        {
            splice(head,carry);
            int i=0;

            while(i<fill&&!empty(counter[i]))
            {
                merge(counter[i],carry);
                swap(carry,counter[i++]);
            }

            swap(carry,counter[i]);

            if(i==fill)++fill;
        }

        for(int i=1;i<fill;++i)
            merge(counter[i],counter[i-1]);
        
        return counter[fill-1];
    }
};

ListNode* init()
{
    int n,x;
    cin>>n>>x;
    --n;

    ListNode*p=new ListNode(x,nullptr),*ans=p;

    while(n--)
    {
        cin>>x;
        p->next=new ListNode(x,nullptr);
        p=p->next;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    ListNode*p=init();
    Solution one;
    one.sortList(p);


    cout<<endl;
    system("pause");
    return 0;
}
