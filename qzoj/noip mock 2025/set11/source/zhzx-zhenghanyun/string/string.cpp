#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int T, id, n, m;

string s, t;

bitset<N> f[2], ch[26];

inline void solve() {
	cin >> s >> t;
	n = s.size(), m = t.size();
	s = "#" + s, t = "#" + t;
	for (int i = 0; i < 26; ++i) {
		ch[i].reset();
	}
	for (int i = 1; i <= n; ++i) {
		ch[s[i] - 'a'][i] = 1;
	}
	f[1][0] = 1;
	for (int i = 1; i <= m; ++i) {
		swap(f[0], f[1]);
		if (t[i] == t[i - 1]) {
			f[1] |= (f[0] << 1) & ch[t[i] - 'a'];
		} else {
			f[1] = (f[0] << 1) & ch[t[i] - 'a'];
		}
	}
	if (f[1][n]) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}

int main() {
	assert(freopen("string.in", "r", stdin));
	assert(freopen("string.out", "w", stdout));
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> T >> id;
	while (T--) {
		solve();
	}
	return 0;
}