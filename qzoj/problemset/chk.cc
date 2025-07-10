#include <bits/stdc++.h>
using namespace std;

typedef long long lld;

const int maxN = int(2e6+7);
const int T = 4*maxN;
const lld mod = 998244353;
const lld inf64 = 0x3f3f3f3f3f3f3f3f;

int n, k; vector<pair<int,lld>> nxt[maxN];
lld ans = inf64;
int sz[maxN], ht[maxN], son[maxN];
lld dis[maxN], dis_tot[maxN];
lld dp[maxN], add[maxN];
int dfn[maxN], pdfn;
// lld val[T], add[T];

void DFS(int u, int fa)
{
    sz[u] = 1;
    ht[u] = 1;
    son[u] = -1;
    for (auto [v, w] : nxt[u])
        if (v != fa)
        {
            DFS(v, u);
            // ht[u] = max(ht[u], ht[v] + 1);
            if (ht[v] + 1 > ht[u])
            {
                son[u] = v;
                ht[u] = ht[v] + 1;
            }
            sz[u] += sz[v];
            dis[u] += dis[v] + w * sz[v];
        }
}

void DFS2(int u, int fa, lld dis_fa, lld faw)
{
    dis_tot[u] = dis[u] + dis_fa + faw * (n - sz[u]);
    for (auto [v, w] : nxt[u])
        if (v != fa)
        {
            DFS2(v, u, dis_tot[u] - dis[v] - w * sz[v], w);
        }
}

// #define ls (v << 1)
// #define rs (ls | 1)
// #define mid ((l + r) >> 1)
// void upd(int v, lld x)
// {
//     val[v] += x;
//     add[v] += x;
//     val[v] = min(val[v], inf64);
// }
// void down(int v)
// {
//     upd(ls, add[v]);
//     upd(rs, add[v]);
//     add[v] = 0;
// }
// void mdf(int v, int l, int r, int L, int R, lld x)
// {
//     if (L <= l && R >= r)
//     {
//         upd(v, x);
//         return;
//     }
//     down(v);
//     if (L <= mid)
//         mdf(ls, l, mid, L, R, x);
//     if (R > mid)
//         mdf(rs, mid + 1, r, L, R, x);
// }
// lld &get(int v, int l, int r, int p)
// {
//     // fprintf(stderr, "%d %d %d ***\n", l, r, p);
//     if (l == r)
//         return val[v];
//     down(v);
//     if (p <= mid)
//         return get(ls, l, mid, p);
//     return get(rs, mid + 1, r, p);
// }

int P(int u, int d) { return dfn[u] + d - 1; }
void DFS3(int u, int fa)
{
    // fprintf(stderr, "in %d\n", u);
    dfn[u] = ++pdfn;
    // get(1, 1, n, P(u, 1)) = dis[u];
    dp[P(u, 1)] = dis[u];
    // memset(dp[u], 0x3f, sizeof(dp[u]));
    // memset(tmp, 0x3f, sizeof(tmp));
    // dp[u][1] = dis[u];
    // tmp[1] = 0;
    // lld sum = dis[u];
    if (son[u] == -1)
    {
        // fprintf(stderr, "out %d\n", u);
        return;
    }
    DFS3(son[u], u);
    // upd(1, 1, n, P(u, 1), dis[u]);
    lld ww;
    for (auto [v, w] : nxt[u])
        if (v == son[u])
            ww = w;
    // if (k >= 2)
    //     mdf(1, 1, n, P(u, 2), P(u, min(k, ht[u])), dis[u] - (dis[son[u]] + ww * sz[son[u]]));
    add[u] = add[son[u]];
    // dp[P(u, 1)] -= add[son[u]];
    add[u] += dis[u] - (dis[son[u]] + ww * sz[son[u]]);
    dp[P(u, 1)] -= add[u];
    if (k <= ht[u])
        // ans = min(ans, get(1, 1, n, P(u, k)) + dis_tot[u] - dis[u]);
        ans = min(ans, dp[P(u, k)] + add[u] + dis_tot[u] - dis[u]);
    for (auto [v, w] : nxt[u])
        if (v != fa && v != son[u])
        {
            // sum -= dis[v] + w * sz[v];
            DFS3(v, u);
            for (int d = 1; d <= ht[v]; ++d)
            {
                if (d < k && k - d <= ht[u])
                {
                    // lld v1 = get(1, 1, n, P(u, k - d));
                    // lld v2 = get(1, 1, n, P(v, d));
                    lld v1 = dp[P(u, k - d)] + add[u];
                    lld v2 = dp[P(v, d)] + add[v];
                    if (v1 < inf64 && v2 < inf64)
                        ans = min(ans, v1 - (dis[v] + w * sz[v]) + v2 + dis_tot[u] - dis[u]);
                }
            }
            for (int d = 1; d <= ht[v]; ++d)
            {
                // lld &it = get(1, 1, n, P(u, d + 1));
                // fprintf(stderr, "%d %d %d %d\n", v, d, dfn[v], P(v, d));
                // lld va = get(1, 1, n, P(v, d));
                lld &it = dp[P(u, d + 1)];
                lld va = dp[P(v, d)] + add[v];
                if (va < inf64)
                    it = min(it, va + dis[u] - (dis[v] + w * sz[v]) - add[u]);
            }
        }
    // fprintf(stderr, "out %d\n", u);
}

lld qpow(lld a, int n = mod - 2)
{
    lld ret = 1;
    while (n)
    {
        if (n & 1)
            (ret *= a) %= mod;
        (a *= a) %= mod, n >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i)
    {
        int u, v; lld w;
        scanf("%d%d%lld", &u, &v, &w);
        nxt[u].push_back({v, w});
        nxt[v].push_back({u, w});
    }
    DFS(1, 0);
    DFS2(1, 0, 0, 0);
    // for (int i = 1; i <= n; ++i)
    //     fprintf(stderr, "%d%c", son[i], " \n"[i == n]);
    // if (n <= 3000)
    // memset(val, 0x3f, sizeof(val));
    memset(dp, 0x3f, sizeof(dp));
    DFS3(1, 0);
    if (k == 1)
    {
        for (int i = 1; i <= n; ++i)
            ans = min(ans, dis_tot[i]);
    }
    if (ans >= inf64)
        printf("-1\n");
    else
        printf("%lld\n", ans % mod * qpow(n) % mod);
    return 0;
}