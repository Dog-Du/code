using namespace std;
#include<iostream>

const int maxn = 1e5 + 10;

struct node {
	int v[8] = { 0 };
}t[maxn << 2];

void pushup(node& x, node& l, node& r)
{
	int p1 = 0, p2 = 0, p = 0;

	while (p < 8 && p1 < 8 && p2 < 8)
	{
		if (l.v[p1] > r.v[p2])x.v[p++] = l.v[p1++];
		else x.v[p++] = r.v[p2++];
	}
}

void modify(int x, int l, int r, int& dist, int v)
{
	if (l == r)
	{
		t[x].v[0] = v;
		return;
	}

	int mid = l + r >> 1;

	if (mid >= dist)modify(x << 1, l, mid, dist, v);
	else modify(x << 1 | 1, mid + 1, r, dist, v);

	pushup(t[x], t[x << 1], t[x << 1 | 1]);
}


node query(int x, int l, int r, int& L, int& R)
{
	if (l >= L && r <= R)
	{
		return t[x];
	}

	int mid = l + r >> 1;
	node ans, t1, t2;

	if (mid >= L)t1 = query(x << 1, l, mid, L, R);
	if (mid < R)t2 = query(x << 1 | 1, mid + 1, r, L, R);

	pushup(ans, t1, t2);

	return ans;
}

int n, m, x, y;
char op;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;

	while (m--)
	{
		cin >> op >> x >> y;

		if (op == 'C')modify(1, 1, n, x, y);
		else cout << query(1, 1, n, x, y).v[7] << '\n';
	}
	return 0;
}
