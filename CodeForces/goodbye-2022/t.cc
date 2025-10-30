#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 300005;
const LL mod = 998244353;
int n, k, cnt = 0, fir[N], nxt[N << 1], to[N << 1], fa[N];
LL ans = 0, p[N], s[N];
void ade(int u, int v) {
    cnt++, nxt[cnt] = fir[u], fir[u] = cnt, to[cnt] = v;
    cnt++, nxt[cnt] = fir[v], fir[v] = cnt, to[cnt] = u;
}
LL qpow(LL x, LL y) {
    LL sum = 1;
    while (y) {
        if (y & 1) sum = sum * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return sum;
}
void dfs(int r, int f) {
    fa[r] = f, s[r] = p[r];
    for (int i = fir[r]; i; i = nxt[i])
        if (to[i] != f)
            dfs(to[i], r), s[r] += s[to[i]];
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, x; i <= k; i++) scanf("%d", &x), p[x] = 1;
    for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), ade(u, v);
    dfs(1, 0);
    LL inv2 = qpow(2, mod - 2);
    for (int i = 1; i <= cnt; i += 2) {
        int u = to[i], v = to[i + 1];
        if (fa[v] != u) swap(u, v);//限定 u 为 v 的父亲
        ans = ((ans
        + p[u] * p[v] % mod * s[v] % mod * (k - s[v]) % mod
        + (1 - p[u]) * (1 - p[v]) % mod * s[v] % mod * (k - s[v]) % mod
        + (1 - p[u]) * p[v] % mod * (s[v] * (k - s[v]) % mod + (s[v] - 1) * (k - s[v] + 1) % mod) % mod * inv2 % mod
        + p[u] * (1 - p[v]) % mod * (s[v] * (k - s[v]) % mod + (s[v] + 1) * (k - s[v] - 1) % mod) % mod * inv2 % mod) % mod + mod) % mod;
        p[u] = p[v] = (p[u] + p[v]) * inv2 % mod;//概率转移
    }
    printf("%lld", (ans * qpow(1ll * k * (k - 1) / 2 % mod, mod - 2) % mod + mod) % mod);
    return 0;
}
