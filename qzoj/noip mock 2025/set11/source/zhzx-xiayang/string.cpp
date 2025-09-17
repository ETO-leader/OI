#include <bits/stdc++.h>
//#define FILE ""
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 1e5 + 5, M = 2000 + 5, O = 20 + 5, L = 2e4 + 5, S = 26;

int n, m;

string s, t;

namespace case1 {
	bitset<L> dp[L];
	bitset<L> f[S], tmp[S];
	void solve() {
		for (int i = 0; i <= m; ++i) {
			dp[i].reset();
		}
		for (int i = 0; i < S; ++i) {
			f[i].reset();
		}
		for (int i = 1; i <= n; ++i) {
			f[s[i] - 'a'][i] = 1;
		}
		dp[0][0] = 1;
		tmp[s[1] - 'a'] = dp[0] << 1;
		for (int i = 1; i <= m; ++i) {
			dp[i] = tmp[t[i] - 'a'];
			if (i >= 2 && t[i] == t[i - 1]) {
				dp[i] |= dp[i - 2];
			}
			for (int j = 0; j < S; ++j) {
				tmp[j] = (dp[i] << 1) & f[j];
			}
		}
		if (dp[m][n]) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
}
namespace case2 {
	bool dp[O][N];
	void solve() {
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 0; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (s[i] == t[j]) {
					dp[i][j] |= dp[i - 1][j - 1];
				}
				if (j >= 2 && t[j] == t[j - 1]) {
					dp[i][j] |= dp[i][j - 2];
				}
			}
		}
		if (dp[n][m]) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
}
namespace case3 {
	void solve() {
		int cnt = m;
		for (int i = 1; i <= m; ++i) {
			if (t[i] != 'a') {
				if (t[i] == t[i + 1]) {
					++i;
					cnt -= 2;
				}
				else {
					cout << "NO\n";
					return ;
				}
			}
		}
		if ((cnt ^ n) & 1) {
			cout << "NO\n";
		}
		else {
			cout << "YES\n";
		}
	}
}
namespace case4 {
	bool dp[N][O];
	void solve() {
		memset(dp, 0, sizeof(dp));
		int det = m - n;
		dp[0][0] = 1;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= det; ++j) {
				if (s[i] == t[j + i]) {
					dp[i][j] |= dp[i - 1][j];
				}
				if (j >= 2 && t[j + i] == t[j + i - 1]) {
					dp[i][j] |= dp[i][j - 2];
				}
			}
		}
		if (dp[n][det]) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
}

int main() {
	assert(freopen("string.in", "r", stdin));
	assert(freopen("string.out", "w", stdout));

	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T, c;
	cin >> T >> c;
	while (T--) {
		cin >> s >> t;
		n = s.size(), m = t.size();
		s = " " + s, t = " " + t;
		if (c <= 4) {
			case1::solve();
		}
		if (c == 5) {
			case2::solve();
		}
		if (c == 6) {
			case3::solve();
		}
		if (c == 7) {
			case4::solve();
		}
	}

	return 0;
}