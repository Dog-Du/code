typedef struct LIST
{
    LIST *next;
    int data;
} *Linklist;


void init_list(Linklist &list);

// 尾插法初始化
void init(Linklist &list);
void show(Linklist &list);
