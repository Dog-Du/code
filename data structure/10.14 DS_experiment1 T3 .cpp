#include <iostream>

using namespace std;

const int maxn = 1e3 + 5;

class set//采用顺序表存储，以归并思想进行 交并差
{
private:
    int num[maxn] = {0};    // 保证这个数组是升序
    bool ch[26 + 26] = {0}; // 判断字符是否已在
    int num_size = 0;       // 记录数字个数
    int Size = 0;           // 记录整体个数

public:
    int size()
    {
        return Size;
    }

    bool empty() // 判断空否
    {
        return Size == 0;
    }

    void insert(char x) // 重载insert，如果存在，则插入，不存在则不操作 时间复杂度为 O(1)
    {
        if (x >= 'a' && x <= 'z' && !ch[x - 'a'])
            ch[x - 'a'] = 1, ++Size;
        else if (x >= 'A' && x <= 'Z' && !ch[x - 'A' + 26])
            ch[x - 'A' + 26] = 1, ++Size;
    }

    void insert(int x) // 先二分查找存在否，在插入,时间复杂度为 O(n)
    {
        if(num_size>0&&x>num[num_size-1])
        {
            num[num_size++]=x;
            ++Size;
            return;
        }

        int l = 0, r = num_size - 1, mid, t = 0;

        // 二分查找
        while (l <= r)
        {
            mid = l + r >> 1;

            if (num[mid] >= x)
                r = mid - 1, t = mid;
            else
                l = mid + 1;
        }

        // 如果t不等，则用插入排序方法插入
        if (num[t] != x)
        {
            for (int i = num_size; i > t; --i)
                swap(num[i], num[i - 1]);
            num[t] = x;
            ++Size;
            ++num_size;
        }
    }

    set operator+(set &it) // 归并排序方法获得并集并返回结果，时间复杂度:O(n+m)
    {
        set res;
        int ch_size = 0;

        for (int i = 0; i < 52; ++i)
            if (ch[i] || it.ch[i])
                res.ch[i] = 1, ++ch_size;

        int p = 0, p1 = 0, p2 = 0;

        while (p1 < num_size && p2 < it.num_size)
        {
            if (num[p1] < it.num[p2])
            {
                res.num[p++] = num[p1++];
            }
            else if (num[p1] > it.num[p2])
            {
                res.num[p++] = it.num[p2++];
            }
            else
            {
                res.num[p++] = num[p1];
                ++p1, ++p2;
            }
        }

        while (p1 < num_size)
            res.num[p++] = num[p1++];

        while (p2 < it.num_size)
            res.num[p++] = it.num[p2++];

        res.num_size = p;
        res.Size = p + ch_size;

        return res;
    }

    set operator*(set &it) // 归并排序方法获得交集并返回结果，时间复杂度为 O(n+m)
    {
        set res;
        int ch_size = 0;

        for (int i = 0; i < 52; ++i)
            if (ch[i] && it.ch[i])
                res.ch[i] = 1, ++ch_size;

        int p = 0, p1 = 0, p2 = 0;

        while (p1 < num_size && p2 < it.num_size)
        {
            if (num[p1] < it.num[p2])
            {
                ++p1;
            }
            else if (num[p1] > it.num[p2])
            {
                ++p2;
            }
            else
            {
                res.num[p++] = num[p1];
                ++p1, ++p2;
            }
        }

        res.num_size = p;
        res.Size = p + ch_size;

        return res;
    }

    set operator-(set &it)// 归并排序方法求差集并返回结果，时间复杂度 O(n+m)
    {
        set res;
        int ch_size = 0, p = 0;

        for (int i = 0; i < 52; ++i)
            if (ch[i] && !it.ch[i])
                res.ch[i] = 1, ++ch_size;

        int p1 = 0, p2 = 0;

        while (p1 < num_size && p2 < it.num_size)
        {
            if (num[p1] < it.num[p2])
            {
                res.num[p++] = num[p1++];
            }
            else if (num[p1] > it.num[p2])
            {
                ++p2;
            }
            else
            {
                ++p1, ++p2;
            }
        }

        while (p1 < num_size)
            res.num[p++] = num[p1++];

        res.num_size = p;
        res.Size = p + ch_size;

        return res;
    }

    void show() // 先数字展示，再字母展示
    {
        for (int i = 0; i < num_size; ++i)
            cout << num[i] << ' ';

        for (int i = 0; i < 26; ++i)
            if (ch[i])
                cout << (char)('a' + i) << ' ';

        for (int i = 26; i < 52; ++i)
            if (ch[i])
                cout << (char)('A' + i - 26) << ' ';

        cout << endl;
    }
};

int main()
{
    set a, b;
    a.insert('a');
    a.insert('b');
    a.insert('b');
    a.insert('c');
    a.insert(100);
    a.insert(985);
    a.insert(555);
    a.insert(666);
    b.insert('b');
    b.insert('d');
    b.insert(1);
    b.insert(999);
    b.insert(666);

    (a + b).show();
    (a * b).show();
    (a - b).show();

    cout << endl;
    system("pause");
    return 0;
}
