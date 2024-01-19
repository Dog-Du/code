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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        for(auto p=head;p->next!=nullptr;p=p->next->next)
            p->next=new ListNode(__gcd(p->val,p->next->val),p->next);
        return  head;
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int a[][3]={1,2,3,4,5,6,7};
    int b=10;
    void* c=&b;
    cout<<*c;
    cout<<endl;
    system("pause");
    return 0;
}
