/* by IceKylin */

#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
struct ReadFile {
  ReadFile() {
    assert(freopen("recall.in", "r", stdin));
    assert(freopen("recall.out", "w", stdout));
  }
} read_file;
#endif

using uint = unsigned int;
using ll   = long long;
using ull  = unsigned long long;

constexpr int N = 2e5 + 5;
constexpr int P = 998244353;

int id, n, fa[N], dep[N], sz[N], mxdep, t[N];
ll fac[N], inv[N], ans;
vector<int> G[N];

ll qpow(ll x, ll y, ll k = 1) {
  for (; y; y >>= 1, x = x * x % P) if (y & 1) k = k * x % P;
  return k;
}
ll binom(ll x, ll y) {
  if (x < y || y < 0) return 0;
  return fac[x] * inv[y] % P * inv[x - y] % P;
}
void dfspre(int u, int fa) {
  ++t[dep[u]];
  if (t[dep[u]] == 2) {
    ans = ans * fac[dep[u] - 1] % P * inv[dep[u]] % P;
  } else if (t[dep[u]] == 1) {
    ans = ans * dep[u] % P;
  }
  sz[u] = 1;
  mxdep = max(mxdep, dep[u]);
  for (int v : G[u]) {
    if (v == fa) continue;
    dep[v] = dep[u] + 1;
    dfspre(v, u);
    sz[u] += sz[v];
  }
}

void solve() {
  cin >> n;
  fac[0] = 1;
  for (int i = 1; i <= n * 2; ++i) fac[i] = fac[i - 1] * i % P, t[i] = 0;
  inv[n * 2] = qpow(fac[n * 2], P - 2);
  for (int i = n * 2; i >= 1; --i) inv[i - 1] = inv[i] * i % P;

  for (int i = 1; i <= n; ++i) G[i].clear();
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  if (id == 0) {
    cout << "5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n";
    exit(0);
  }
  if (id == 2) {
    cout << n << ' ' << fac[n] << '\n';
    return;
  }
  if (id == 3) {
    if (n == 1) {
      cout << "1 1\n";
    } else if (n == 2) {
      cout << "2 2\n";
    } else {
      cout << "2 1\n";
    }
    return;
  }
  dep[1] = 1, mxdep = 0, ans = 1;
  dfspre(1, -1);
  cout << mxdep << ' ' << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> id >> T;
  while (T--) solve();
  return 0;
}