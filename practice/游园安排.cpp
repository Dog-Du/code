using namespace std;
#include<iostream>
#include<vector>
#include<string>
#include<set> 
#include<algorithm>

char ch;
vector<string> name, res, ans;
string s;
vector<int> len;

int main()
{
	while (cin >> ch)
	{
		if (ch >= 'A' && ch <= 'Z' && !s.empty())
		{
			name.push_back(s);
			s.clear();
		}
		s.push_back(ch);
	}

	name.push_back(s);

	for (int i = 0, l, r, mid, t; i < name.size(); ++i)
	{
		if (res.empty() || name[i] > res.back())
		{
			res.push_back(name[i]);
			len.push_back((int)res.size() - 1);
			continue;
		}

		l = 0, r = res.size() - 1;

		while (l <= r)
		{
			mid = l + r >> 1;

			if (res[mid] >= name[i])
			{
				t = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}

		res[t] = name[i];
		len.push_back(t);
	}

	int l = res.size() - 1;

	for (int i = name.size() - 1; l >= 0; --i)
	{
		if (len[i] == l)
		{
			ans.push_back(name[i]);
			--l;
		}

	}

	for (int i = ans.size() - 1; i >= 0; --i)
		cout << ans[i];
	return 0;
}
