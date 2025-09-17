/* by IceKylin */

#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
struct ReadFile {
  ReadFile() {
    assert(freopen("grandiloquence.in", "r", stdin));
    assert(freopen("grandiloquence.out", "w", stdout));
  }
} read_file;
#endif

using uint = unsigned int;
using ll   = long long;
using ull  = unsigned long long;

constexpr int N = 4e5 + 5;

int id;
int n, m, k, fa[N], col[N], lstans;

vector<int> G[N];

void dfs1(int u, int c, int d) {
  col[u] = (d + c - 1 + k) % k + 1;
  for (int v : G[u]) {
    dfs1(v, c, d + 1);
  }
}

int dfs2(int u, int c) {
  int res = (col[u] == c);
  for (int v : G[u]) {
    res += dfs2(v, c);
  }
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> id;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> fa[i];
    G[fa[i]].push_back(i);
  }
  int cnt_node = n;
  while (m--) {
    int op, u, c;
    cin >> op >> u;
    if (op != 3) {
      cin >> c;
      if (id % 2 == 0) {
        u ^= lstans, c ^= lstans;
      }
      if (op == 1) {
        dfs1(u, c, 0);
      } else {
        cout << (lstans = dfs2(u, c)) << '\n';
      }
    } else {
      if (id % 2 == 0) {
        u ^= lstans;
      }
      fa[++cnt_node] = u;
      G[u].push_back(cnt_node);
    }
  }
  return 0;
}