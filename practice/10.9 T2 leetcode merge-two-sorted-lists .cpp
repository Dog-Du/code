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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* ans=new ListNode,* p=ans;

        while(list1&&list2)
        {
            if(list1->val>=list2->val)
            {
                p->next=list2;
                list2=list2->next;
                p=p->next;
            }
            else
            {
                p->next=list1;
                list1=list1->next;
                p=p->next;
            }
        }

        if(list1)p->next=list1;
        else p->next=list2;

        p=ans->next;
       // free(ans);
        
        return p->next;
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
