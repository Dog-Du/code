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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode*slow=head,*fast=head,*temp,*P=new ListNode,*pre=P;
        P->next=head;

        while(slow)
        {
            fast=slow->next;
            bool flag=0;

            while(fast&&fast->val==slow->val)
            {
                temp=fast->next;
                //free(fast);
                fast=temp;
                slow->next=fast;
                flag=1;
            }

            if(flag)
            {
                temp=slow;
                pre->next=slow->next;
                //free(slow);
            }
            else
                pre=slow;

            slow->next=fast;
            slow=fast;
        }

        //free(P);

        return P->next;
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
