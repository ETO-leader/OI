#include<bits/stdc++.h>
using namespace std;

void solve()
{
	int n, m;
	cin >> n >> m;

	int mx = 0, mn = 0;

	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;

		int cnt0 = 0, cnt1 = 0, num1 = 0;

		for (int j = 0; j < m; j++)
			if (s[j] == '1') num1++;

		for (int j = 1; j < m; j++)
		{
			if (s[j] + s[j - 1] != '1' + '1')
			{
				cnt0++;
				j++;
			}
		}
		for (int j = 1; j < m; j++)
		{
			if (s[j] + s[j - 1] == '1' + '1')
			{
				cnt1++;
				j++;
			}
		}

		mx += num1 - max(0, m / 4 - cnt0);
		mn += num1 - min(m / 4, cnt1);
	}

	cout << mn << ' ' << mx;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
}