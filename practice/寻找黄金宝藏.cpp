using namespace std;
#include<iostream>
#include<algorithm>

//���ִ𰸣���ǰ׺���ж� �Ƿ����һ������� ��λ�����ڵ���0 

const int maxn = 1e5 + 10;
int n, k;
int a[maxn], f[maxn];

bool check(int x)
{
	int mi = 0, pos1 = 0;//��ʼֵΪ0,0
	int ma = -1e9, pos2 = -1;

	for (int i = 1; i <= n; ++i)
	{
		if (a[i] > x)f[i] = f[i - 1] + 1;
		else if (a[i] < x)f[i] = f[i - 1] - 1;
		else f[i] = f[i - 1];

		if (mi > f[i])//������mi����ߣ����Ե��ڵ�ʱ��ˢ��
		{
			mi = f[i];
			pos1 = i;
		}

		if (i>=k && ma <= f[i])//������ma���ұߣ����Ե��ڵ�ʱ��ˢ��
		{
			ma = f[i];
			pos2 = i;
		}

		if (i >= k && ma - mi >= 0 && pos2 - pos1 + 1 >= k)//i>=k ��ֵ���ڵ���0 ���䳤�ȴ��ڵ���k ͬʱ����
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
