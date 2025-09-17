/* by IceKylin */

#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
struct ReadFile {
  ReadFile() {
    assert(freopen("string.in", "r", stdin));
    assert(freopen("string.out", "w", stdout));
  }
} read_file;
#endif

using uint = unsigned int;
using ll   = long long;
using ull  = unsigned long long;

constexpr int N = 1e5 + 5;

int T, id;

string s, t;

bool be = 0;

bitset<N> dp[2], pre[26], ppre;

bool ed = 0;

void solve() {
  cin >> s >> t;
  int n = s.size(), m = t.size();
  s = ' ' + s, t = ' ' + t;

  if (id == 6) {
    if ((m - n) & 1) {
      cout << "NO\n";
      return;
    }
    for (int i = 1; i <= m; ++i) {
      if (t[i] != ' ' && t[i] != 'a') {
        if (i == m || t[i] != t[i + 1]) {
          cout << "NO\n";
          return;
        }
        t[i] = t[i + 1] = ' ';
      }
    }
    int lcnt = 0;
    for (int i = 1; i <= m; ++i) lcnt += (t[i] == 'a');

    for (int i = 1; i < m; ++i) {
      if (lcnt > n && t[i] == 'a' && t[i + 1] == 'a') {
        lcnt -= 2, t[i] = t[i + 1] = ' ';
      }
    }
    cout << (lcnt == n ? "YES\n" : "NO\n");
    return;
  }

  dp[0].set(), dp[1].reset(), ppre.reset();
  for (int i = 0; i < 26; ++i) {
    pre[i].reset();
    for (int j = 1; j <= m; ++j) {
      pre[i][j] = ((t[j] - 'a') == i);
    }
  }
  for (int j = 1; j <= m; ++j) {
    if (t[j] == t[j - 1]) ppre[j] = true;
  }
  for (int i = 1; i <= n; ++i) {
    int op = i & 1;
    dp[op].reset();
    dp[op] = (dp[op ^ 1] << 1) & pre[s[i] - 'a'];
    // dp[op] = dp[op] | ((dp[op] << 2) & ppre);
    for (int j = max(i, 2); j <= min(m, i + m - n); ++j) {
      dp[op][j] = dp[op][j] | (dp[op][j - 2] & ppre[j]);
    }
  }
  cout << (dp[n & 1][m] ? "YES\n" : "NO\n");
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> T >> id;
  while (T--) solve();
  return 0;
}