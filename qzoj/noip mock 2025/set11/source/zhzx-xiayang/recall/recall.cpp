#include <bits/stdc++.h>
//#define FILE ""
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 1e5 + 5, M = 100 + 5, P = 998244353;

void reduce(int &x) {
	if (x >= P) {
		x -= P;
	}
}

int C[M][M];
void init(int len) {
	for (int i = 0; i <= len; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			reduce(C[i][j] = C[i - 1][j] + C[i - 1][j - 1]);
		}
	}
}

int n;

int hd[N], nxt[N << 1], to[N << 1], edc;
void add(int x, int y) {
	++edc;
	nxt[edc] = hd[x];
	to[edc] = y;
	hd[x] = edc;
}

int mx[N], smx[N], dp[M][M][M], dep;

int f[N];

void dfs(int u, int fa, int d) {
	dep = max(dep, d);
	f[u] = 0;
	for (int i = hd[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v == fa) {
			continue;
		}
		dfs(v, u, d + 1);
		f[u] = max(f[v], f[u]);
	}
	++f[u];
	if (f[u] > mx[d]) {
		smx[d] = mx[d];
		mx[d] = f[u];
	}
	else if (f[u] > smx[d]) {
		smx[d] = f[u];
	}
}

void solve() {
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		hd[i] = 0;
	}
	edc = 0;
	for (int i = 1; i <= dep; ++i) {
		mx[i] = smx[i] = 0;
	}
	dep = 0;

	for (int i = 1, x, y; i < n; ++i) {
		cin >> x >> y;
		add(x, y);
		add(y, x);
	}

	dfs(1, 0, 1);

	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= dep; ++i) {
		for (int j = 0; j <= dep; ++j) {
			dp[j][i][i - 1] = 1;
		}
	}
	for (int len = 1; len <= dep; ++len) {
		for (int l = 1; l + len - 1 <= dep; ++l) {
			int r = l + len - 1;
			for (int i = 0; i <= dep - r; ++i) {
				if (smx[r] - i > 1) {
					continue;
				}
				dp[i][l][r] = dp[i + 1][l][r - 1];
				for (int k = l + 1; k <= r; ++k) {
					if (smx[k] - i <= 0) {
						dp[i][l][r] = (dp[i][l][r] + 1ll * dp[i][l][k - 1] * dp[i + 1][k][r - 1] % P * C[r - l][r - k]) % P;
					}
				}
			}
		}
	}
	cout << dep << ' ' << dp[0][1][dep] << '\n';
}

int main() {
	assert(freopen("recall.in", "r", stdin));
	assert(freopen("recall.out", "w", stdout));

	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int c, T;
	cin >> c >> T;
	init(100);
	while (T--) {
		solve();
	}

	return 0;
}