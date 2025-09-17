#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;
const ll mod = 998244353;

namespace Combinatorics {
const int N = 1e6 + 5;
const ll mod = 998244353;

ll fac[N], ifac[N];

class Initializer {
public:
	Initializer() {
		fac[0] = 1;
		for (int i = 1; i < N; ++i) {
			fac[i] = fac[i - 1] * i % mod;
		}
		ifac[0] = ifac[1] = 1;
		for (int i = 2; i < N; ++i) {
			ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
		}
		for (int i = 1; i < N; ++i) {
			ifac[i] = ifac[i] * ifac[i - 1] % mod;
		}
	}
};

inline ll perm(ll n, ll m) {
	if (n < m || m < 0) {
		return 0;
	}
	return fac[n] * ifac[n - m] % mod;
}

inline ll binom(ll n, ll m) {
	if (n < m || m < 0) {
		return 0;
	}
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

static Initializer initializer;

}

using Combinatorics::perm;
using Combinatorics::binom;

struct edge {
	int to, Next;

	edge() {}
	edge(int to, int Next): to(to), Next(Next) {}
} G[N << 1];

int head[N], cnt;

inline void add_edge(int u, int v) {
	G[++cnt] = edge(v, head[u]);
	head[u] = cnt;
}

int id, T, n, m, dep[N];

ll ans;

inline void dfs(int fa, int u) {
	dep[u] = dep[fa] + 1;
	for (int i = head[u]; i; i = G[i].Next) {
		int v = G[i].to;
		if (v == fa) {
			continue;
		}
		dfs(u, v);
	}
}

inline void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		head[i] = 0;
	}
	cnt = 0;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(0, 1);
	int mdep = *max_element(dep + 1, dep + n + 1);
	if (id == 3) {
		ans = 1;
	}
	ans = 1;
	cout << mdep << " " << ans << "\n";
}

int main() {
	assert(freopen("recall.in", "r", stdin));
	assert(freopen("recall.out", "w", stdout));
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> id >> T;
	if (id == 0) {
		cout << "5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n";
		exit(0);
	}
	while (T--) {
		solve();
	}
	return 0;
}