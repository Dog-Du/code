using namespace std;
#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long


//在左端点确定的情况下,__gcd必然不减，而区间长度递增，其差值递减，可以来寻找零点
 
struct node {
	int l, r;
};

const int maxn = 2e5 + 10;

int n;
ll a[maxn], t[maxn << 2];
vector<node> vec;

ll __gcd(ll a, ll b)
{
	return b == 0 ? a : __gcd(b, a % b);
}

void build(int x, int l, int r)
{
	if (l == r)
	{
		t[x] = a[l];
		return;
	}
	int mid = l + r >> 1;

	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);

	t[x] = __gcd(t[x << 1], t[x << 1 | 1]);
	return;
}

ll query(int x, int l, int r, int L, int R)
{
	if (l >= L && r <= R)
	{
		return t[x];
	}

	int mid = l + r >> 1;
	ll ans = 0;

	if (mid >= L)ans = __gcd(query(x << 1, l, mid, L, R), ans);
	if (mid < R)ans = __gcd(query(x << 1 | 1, mid + 1, r, L, R), ans);

	return ans;
}

int main()
{
	cin >> n;

	for (int i = 1; i <= n; ++i)	cin >> a[i];

	build(1, 1, n);

	for (int i = 1, l, r, mid, t; i <= n; ++i)
	{
		l = i, r = n, t = -1;

		while (l <= r)
		{
			mid = l + r >> 1;

			ll temp = query(1, 1, n, i, mid);

			//printf("%d %d %lld\n", i, mid, temp);

			if (temp >= mid - i + 1)
				l = mid + 1;
			else
				r = mid - 1;

			if (temp == mid - i + 1)t = mid;
		}

		if (t != -1)
		{
			vec.push_back({ i,t });
		}

	}

	int ans = (!vec.empty());

	//for(auto &it:vec)printf("%d %d\n",it.l,it.r);
	
	//用贪心串起来 
	for (int i = 1; i < vec.size(); ++i)
	{

		if (vec[i].l <= vec[i - 1].r)
		{
			vec[i].r = min(vec[i].r, vec[i - 1].r);
		}
		else
			++ans;
	}

	cout << ans;
	return 0;
}
