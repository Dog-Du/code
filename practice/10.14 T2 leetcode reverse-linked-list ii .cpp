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
public:

    void insert(ListNode*head,ListNode* p)
    {
        ListNode*temp=head->next;
        head->next=p;
        p->next=temp;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left>=right)return head;

        ListNode* temp=new ListNode;
        temp->next=head;
        ListNode * p=temp;
        int k=left;

        while(--k)p=p->next;

        ListNode *P=p->next,*it=P;

        while(left<=right)
        {
            ListNode *t=it->next;
            insert(p,it);
            it=t;
            ++left;
        }

        P->next=it;

        return temp->next;
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
