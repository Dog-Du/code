using namespace std;
#include<iostream>
#include<algorithm>

//二分答案，用前缀和判断 是否存在一个区间的 中位数大于等于0 

const int maxn = 1e5 + 10;
int n, k;
int a[maxn], f[maxn];

bool check(int x)
{
	int mi = 0, pos1 = 0;//初始值为0,0
	int ma = -1e9, pos2 = -1;

	for (int i = 1; i <= n; ++i)
	{
		if (a[i] > x)f[i] = f[i - 1] + 1;
		else if (a[i] < x)f[i] = f[i - 1] - 1;
		else f[i] = f[i - 1];

		if (mi > f[i])//尽量让mi靠左边，所以等于的时候不刷新
		{
			mi = f[i];
			pos1 = i;
		}

		if (i>=k && ma <= f[i])//尽量让ma考右边，所以等于的时候刷新
		{
			ma = f[i];
			pos2 = i;
		}

		if (i >= k && ma - mi >= 0 && pos2 - pos1 + 1 >= k)//i>=k 差值大于等于0 区间长度大于等于k 同时满足
		{
			return true;
		}
	}

	return false;
}

int main()
{
	cin >> n >> k;

	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		a[i] *= 2;
	}

	int l = 1, r = 2 * n, mid, ans;

	while (l <= r)
	{
		mid = l + r >> 1;

		if (check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}

	cout << 1.0 * ans / 2;
	return 0;
}
