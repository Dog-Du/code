// #include<iostream>

// using namespace std;

// // 基本思想：用a来接受奇数，b来接受偶数，然后用插入排序，边遍历边连接
// // 时间复杂度：O(n^2) 空间复杂度：O(1)


// typedef struct LIST
// {
//     LIST *next;
//     int data;
// } *Linklist;

// void init_list(Linklist &list)
// {
//     Linklist p = new LIST;
//     list = p;
//     list->next = NULL;
// }

// // 尾插法初始化
// void init(Linklist &list)
// {
//     int n, x;
//     Linklist p = list;

//     cin >> n;

//     while (n--)
//     {
//         cin >> x;

//         Linklist temp = new LIST;
//         temp->next = NULL;
//         temp->data = x;

//         p->next = temp;
//         p = p->next;
//     }
// }

// void show(Linklist &list)
// {
//     Linklist p = list;

//     while (p->next != NULL)
//     {
//         cout << p->next->data << ' ';
//         p = p->next;
//     }

//     cout << endl;
//     return;
// }

// void split_list(Linklist &list, Linklist &a, Linklist &b)
// {
//     a->next = NULL, b->next = NULL;

//     for (Linklist p = list->next, p1, p2, pre; p;)
//     {
//         if (p->data % 2 == 0)
//         {

//             // 插入排序思想，进行排序

//             p1 = b->next, pre = b;

//             while (p1 && p1->data > p->data)
//                 pre = p1, p1 = p1->next;

//             p2 = p->next;

//             pre->next = p;
//             p->next = p1;
//             p = p2;
//         }
//         else
//         {
//             p1 = a->next, pre = a;

//             while (p1 && p1->data < p->data)
//                 pre = p1, p1 = p1->next;

//             p2 = p->next;

//             pre->next = p;
//             p->next = p1;
//             p = p2;
//         }
//     }
// }

// void test()
// {
//     Linklist list, a, b;

//     init_list(list);
//     init_list(a);
//     init_list(b);
//     init(list);

//     split_list(list, a, b);

//     show(a);
//     show(b);
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
