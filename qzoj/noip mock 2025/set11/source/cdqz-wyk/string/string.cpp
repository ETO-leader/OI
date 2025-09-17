#include <bits/stdc++.h>
#define LL long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define Let (u<<1)
#define Rit (u<<1|1)
#define lowbit(x) (x&(-x))
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 2005;
const int maxn = 1e5 + 5;
int T, id, n, m, nxt[maxn][30], vis[maxn], f[N][N];
char s[maxn], t[maxn];
void ex_solve() {
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (s[i] == t[j])
				f[i][j] |= f[i - 1][j - 1];
			if (j - 2 >= 0 && t[j - 1] == t[j])
				f[i][j] |= f[i][j - 2];
		}
	if (f[n][m]) cout << "YES\n";
	else cout << "NO\n";
	return ;
}
void solve() {
	for (int c = 0; c < 26; c++)
		nxt[m][c] = m + 1;
	for (int i = m - 1; i >= 0; i--) {
		for (int c = 0; c < 26; c++)
			nxt[i][c] = nxt[i + 1][c];
		nxt[i][(int)(t[i + 1] - 'a')] = i + 1;
	}
	memset(vis, 0, sizeof(vis));
	int now = nxt[0][(int)(s[1] - 'a')];
	vis[now] = 1;
	for (int i = 2; i <= n; i++) {
		now = nxt[now][(int)(s[i] - 'a')];
		vis[now] = 1;
	}
	int last = -1;
	for (int i = 1; i <= m; i++) {
		if (vis[i]) continue;
		if (last == -1) {
			last = i;
			continue;
		}
		if (s[i] != s[last]) {
			cout << "NO\n";
			return ;
		}
		last = -1;
	}
	cout << "YES\n";
	return ;
}
int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T >> id;
	while (T--) {
		cin >> (s + 1) >> (t + 1);
		n = strlen(s + 1);
		m = strlen(t + 1);
		if (n <= 2000 && m <= 2000)
			ex_solve();
		else
			solve();
	}
	return 0;
}
