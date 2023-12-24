// #include "list.h"
// #include <iostream>

// using namespace std;

// // 基本思想：快慢双指针，通过swap进行交换
// // 时间复杂度：O(n) 空间复杂度：O(1)

// void func(Linklist &list)
// {
//     for (Linklist l = list->next, r = list->next; r; r = r->next)
//     {
//         if (r->data < 0)
//         {
//             swap(r->data, l->data);
//             l = l->next;
//         }
//     }
// }

// void partition(Linklist &head)
// {
//     if (head == NULL || head->next == NULL)return;
        
//     //这里可以让p1,p2新建一个头指针，会写的更方便，但这里出于节约空间的考虑，没有新建头节点。

//     Linklist p1 = NULL, p2 = NULL, t1 = NULL, p = head->next, t2 = NULL;

//     while (p)
//     {
//         if (p->data >= 0)
//         {
//             if (!p2)
//             {
//                 p2 = p;
//                 t2 = p2;
//             }
//             else
//             {
//                 p2->next = p;
//                 p2 = p2->next;
//             }
//         }
//         else
//         {
//             if (!p1)
//             {
//                 p1 = p;
//                 t1 = p1;
//             }
//             else
//             {
//                 p1->next = p;
//                 p1 = p1->next;
//             }
//         }

//         p = p->next;
//     }

//     if (p2)
//         p2->next = NULL; // 防止无限循环

//     if (p1)
//         p1->next = t2;

//     head->next = (t1 == NULL) ? t2 : t1;
// }

// void test()
// {
//     Linklist list;

//     init_list(list);
//     init(list);

//     func(list);

//     show(list);
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0), cout.tie(0);

//     int t;
//     cin >> t;

//     while (t--)
//     {
//         test();
//     }

//     cout << endl;
//     system("pause");
//     return 0;
// }
