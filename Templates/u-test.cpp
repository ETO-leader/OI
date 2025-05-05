// #include <cstdio>
// #include <algorithm>
// #define Mod 998244353
// #define N 30
// #define M 15
// #define V 32768
// #define W 59049
// using namespace std;

// int n, m, d[N], p[N], q[N], f[M + 1][V], g[M + 1][N + 1][V], cnt[V], inv[N + 1], len, pl[M], idn[M];
// int h[W], tot[M + 1], w[V], lmt[M];
// pair<int, int> P[N];

// int read() {
//     int num = 0;
//     char c = getchar();
//     while (c < '0' || c > '9') {
//         c = getchar();
//     }
//     while (c >= '0' && c <= '9') {
//         num = num * 10 + (c & 15), c = getchar();
//     }
//     return num;
// }

// void init() {
//     for (int i = 1; i < V; i ++) {
//         cnt[i] = cnt[i >> 1] + (i & 1);
//     }
//     inv[1] = 1;
//     for (int i = 2; i <= N; i ++) {
//         inv[i] = Mod - 1ll * Mod / i * inv[Mod % i] % Mod; 
//     }
//     n = read(), m = n >> 1;
//     for (int i = 0; i < n; i ++) {
//         d[i] = read();
//     }
//     for (int i = 0; i < n; i ++) {
//         p[i] = read();
//     }
//     for (int i = 0; i < n; i ++) {
//         q[i] = read();
//     }
//     return;
// }

// void add(int &x, int y) {
//     x += y, x -= ((x >= Mod) ? Mod : 0);
//     return;
// }

// void calculate() {
//     f[0][0] = 1;
//     for (int i = 0; i < m;) {
//         int x = (Mod + 1 - p[i]) % Mod;
//         for (int j = 0; j < (1 << i); j ++) {
//             f[i][1 << i | j] = 1ll * p[i] * f[i][j] % Mod, f[i][j] = 1ll * x * f[i][j] % Mod;
//         }
//         x = (Mod + 1 - q[i ++]) % Mod;
//         for (int j = 0; j < (1 << i); j ++) {
//             f[i][j] = 1ll * x * f[i - 1][j] % Mod;
//         }
//         for (int j = 1; j < (1 << i); j ++) {
//             x = 1ll * q[i - 1] * inv[cnt[j]] % Mod * f[i - 1][j] % Mod;
//             for (int k = 0; k < i; k ++) {
//                 if ((j >> k & 1) && i <= k + d[k]) {
//                     add(f[i][j ^ (1 << k)], x);
//                 }
//             }
//         }
//     }
//     for (int i = 0; i <= n; i ++) {
//         for (int j = 0; j < (1 << n >> m); j ++) {
//             g[n - m][i][j] = 1;
//         }
//     }
//     for (int i = n - m - 1; ~i; i --) {
//         int x = (Mod + 1 - q[i + m]) % Mod;
//         for (int j = i + m + 1; ~j; j --) {
//             int y = 1ll * q[i + m] * inv[j] % Mod;
//             for (int k = 0; k < (1 << n >> m); k ++) {
//                 if (k >> i & 1) {
//                     g[i + 1][j][k] = (j ? (1ll * y * g[i + 1][j - 1][k] % Mod) : 0);
//                 } else {
//                     g[i + 1][j][k] = 1ll * x * g[i + 1][j][k] % Mod;
//                 }
//             }
//         }
//         x = (Mod + 1 - p[i + m]) % Mod;
//         for (int j = 0; j <= i + m; j ++) {
//             for (int k = 0; k < (1 << n >> m); k ++) {
//                 g[i][j][k] = g[i + 1][j + 1][k];
//                 for (int l = i; l < i + d[i + m] && l < n - m; l ++) {
//                     if (k >> l & 1) {
//                         continue;
//                     }
//                     add(g[i][j][k], g[i + 1][j + 1][k | (1 << l)]);
//                 }
//                 g[i][j][k] = (1ll * p[i + m] * g[i][j][k] + 1ll * x * g[i + 1][j][k]) % Mod;
//             }
//         }
//     }
//     for (int i = 0; i <= m; i ++) {
//         for (int j = 0; j < (1 << n >> m); j ++) {
//             if (i < cnt[j]) {
//                 g[0][i][j] = 0;
//             }
//         }
//     }
//     for (int i = 0; i < m; i ++) {
//         P[i] = make_pair(max(min(i + d[i], n), m), i);
//     }
//     for (int i = m; i < n; i ++) {
//         P[i] = make_pair(i + 1, -i);
//     }
//     sort(P, P + n), reverse(P, P + n);
//     int indl = 0, indr = n;
//     while (indl < indr && P[indl].second < 0) {
//         lmt[-P[indl ++].second - m] = -1;
//     }
//     while (indr > indl && P[indr - 1].second >= 0) {
//         idn[P[-- indr].second] = -1;
//     }
//     while (indl < indr) {
//         int a = 0, b = 0;
//         while (indl < indr && P[indl].second >= 0) {
//             idn[P[indl ++].second] = len, a ++;
//         }
//         while (indl < indr && P[indl].second < 0) {
//             lmt[-P[indl ++].second - m] = len, b ++;
//         }
//         pl[len ++] = max(a, b) + 1;
//     }
//     tot[0] = 1;
//     for (int i = 0; i < len; i ++) {
//         tot[i + 1] = 1ll * pl[i] * tot[i] % Mod;
//     }
//     int ans = 0;
//     for (int i = 0; i <= m; i ++) {
//         for (int j = 0; j < tot[len]; j ++) {
//             h[j] = 0;
//         }
//         for (int j = 0; j < (1 << n >> m); j ++) {
//             int pos = 0;
//             for (int k = 0; k < n - m; k ++) {
//                 if (j >> k & 1) {
//                     if (!~lmt[k]) {
//                         pos = -1;
//                         break;
//                     }
//                     pos += tot[lmt[k]];
//                 }
//             }
//             if (~pos) {
//                 add(h[pos], g[0][i][j]);
//             }
//         }
//         for (int j = 0; j < i; j ++) {
//             for (int k = 0; k < tot[len]; k ++) {
//                 if (!h[k]) {
//                     continue;
//                 }
//                 int re = j;
//                 for (int l = 0, s = k; l < len; s = s / pl[l ++]) {
//                     re -= s % pl[l];
//                     if (re < 0) {
//                         for (int d = 0, r = k; d < l; r = r / pl[d ++]) {
//                             if ((r + 1) % pl[d]) {
//                                 add(h[k - tot[l] + tot[d]], h[k]);
//                             }
//                         }
//                         break;
//                     }
//                 }
//             }
//         }
//         for (int j = 0; j < (1 << m); j ++) {
//             int s = 0;
//             for (int k = 0; k < m; k ++) {
//                 if (j >> k & 1) {
//                     if (!~idn[k]) {
//                         s = -1;
//                         break;
//                     }
//                     s += tot[idn[k]];
//                 }
//             }
//             if (!~s) {
//                 w[j] = 0;
//                 continue;
//             }
//             w[j] = h[s];
//             for (int k = 0, r = s; k < len; r = r / pl[k ++]) {
//                 for (int l = r % pl[k]; l; l --) {
//                     w[j] = 1ll * l * w[j] % Mod;
//                 }
//             }
//         }
//         for (int j = 0, step = 2; j < m; j ++, step = step << 1) {
//             for (int lft = 0; lft < (1 << m); lft += step) {
//                 for (int rgt = 0; rgt < (1 << j); rgt ++) {
//                     add(w[lft | (1 << j) | rgt], w[lft | rgt]);
//                 }
//             }
//         }
//         for (int j = 0; j < (1 << m); j ++) {
//             if (cnt[j] == i) {
//                 ans = (ans + 1ll * f[m][j] * w[j]) % Mod;
//             }
//         }
//     }
//     ans = (Mod + 1 - ans) % Mod;
//     printf("%d\n", ans);
//     return;
// }

// void solve() {
//     init();
//     calculate();
//     return;
// }

// int main() {
//     solve();
//     return 0;
// }

#include <cstdio>
#include <algorithm>
#define Mod 998244353
#define N 30
#define M 15
#define V 32768
#define W 59049
using namespace std;

int n, m, d[N], p[N], q[N], f[M + 1][V], g[M + 1][N + 1][V], cnt[V], inv[N + 1], len, pl[M], idn[M];
int h[W], tot[M + 1], w[V], lmt[M];
pair<int, int> P[N];

int read() {
    int num = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        num = num * 10 + (c & 15), c = getchar();
    }
    return num;
}

void init() {
    for (int i = 1; i < V; i ++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
    inv[1] = 1;
    for (int i = 2; i <= N; i ++) {
        inv[i] = Mod - 1ll * Mod / i * inv[Mod % i] % Mod; 
    }
    n = read(), m = n >> 1;
    for (int i = 0; i < n; i ++) {
        p[i] = read(), q[i] = read(), d[i] = read();
    }
    return;
}

void add(int &x, int y) {
    x += y, x -= ((x >= Mod) ? Mod : 0);
    return;
}

void calculate() {
    f[0][0] = 1;
    for (int i = 0; i < m;) {
        int x = (Mod + 1 - p[i]) % Mod;
        for (int j = 0; j < (1 << i); j ++) {
            f[i][1 << i | j] = 1ll * p[i] * f[i][j] % Mod, f[i][j] = 1ll * x * f[i][j] % Mod;
        }
        x = (Mod + 1 - q[i ++]) % Mod;
        for (int j = 0; j < (1 << i); j ++) {
            f[i][j] = 1ll * x * f[i - 1][j] % Mod;
        }
        for (int j = 1; j < (1 << i); j ++) {
            x = 1ll * q[i - 1] * inv[cnt[j]] % Mod * f[i - 1][j] % Mod;
            for (int k = 0; k < i; k ++) {
                if ((j >> k & 1) && i <= k + d[k]) {
                    add(f[i][j ^ (1 << k)], x);
                }
            }
        }
    }
    for (int i = 0; i <= n; i ++) {
        for (int j = 0; j < (1 << n >> m); j ++) {
            g[n - m][i][j] = 1;
        }
    }
    for (int i = n - m - 1; ~i; i --) {
        int x = (Mod + 1 - q[i + m]) % Mod;
        for (int j = i + m + 1; ~j; j --) {
            int y = 1ll * q[i + m] * inv[j] % Mod;
            for (int k = 0; k < (1 << n >> m); k ++) {
                if (k >> i & 1) {
                    g[i + 1][j][k] = (j ? (1ll * y * g[i + 1][j - 1][k] % Mod) : 0);
                } else {
                    g[i + 1][j][k] = 1ll * x * g[i + 1][j][k] % Mod;
                }
            }
        }
        x = (Mod + 1 - p[i + m]) % Mod;
        for (int j = 0; j <= i + m; j ++) {
            for (int k = 0; k < (1 << n >> m); k ++) {
                g[i][j][k] = g[i + 1][j + 1][k];
                for (int l = i; l < i + d[i + m] && l < n - m; l ++) {
                    if (k >> l & 1) {
                        continue;
                    }
                    add(g[i][j][k], g[i + 1][j + 1][k | (1 << l)]);
                }
                g[i][j][k] = (1ll * p[i + m] * g[i][j][k] + 1ll * x * g[i + 1][j][k]) % Mod;
            }
        }
    }
    for (int i = 0; i <= m; i ++) {
        for (int j = 0; j < (1 << n >> m); j ++) {
            if (i < cnt[j]) {
                g[0][i][j] = 0;
            }
        }
    }
    for (int i = 0; i < m; i ++) {
        P[i] = make_pair(max(min(i + d[i], n), m), i);
    }
    for (int i = m; i < n; i ++) {
        P[i] = make_pair(i + 1, -i);
    }
    sort(P, P + n), reverse(P, P + n);
    int indl = 0, indr = n;
    while (indl < indr && P[indl].second < 0) {
        lmt[-P[indl ++].second - m] = -1;
    }
    while (indr > indl && P[indr - 1].second >= 0) {
        idn[P[-- indr].second] = -1;
    }
    while (indl < indr) {
        int a = 0, b = 0;
        while (indl < indr && P[indl].second >= 0) {
            idn[P[indl ++].second] = len, a ++;
        }
        while (indl < indr && P[indl].second < 0) {
            lmt[-P[indl ++].second - m] = len, b ++;
        }
        pl[len ++] = max(a, b) + 1;
    }
    tot[0] = 1;
    for (int i = 0; i < len; i ++) {
        tot[i + 1] = 1ll * pl[i] * tot[i] % Mod;
    }
    int ans = 0;
    for (int i = 0; i <= m; i ++) {
        for (int j = 0; j < tot[len]; j ++) {
            h[j] = 0;
        }
        for (int j = 0; j < (1 << n >> m); j ++) {
            int pos = 0;
            for (int k = 0; k < n - m; k ++) {
                if (j >> k & 1) {
                    if (!~lmt[k]) {
                        pos = -1;
                        break;
                    }
                    pos += tot[lmt[k]];
                }
            }
            if (~pos) {
                add(h[pos], g[0][i][j]);
            }
        }
        for (int j = 0; j < i; j ++) {
            for (int k = 0; k < tot[len]; k ++) {
                if (!h[k]) {
                    continue;
                }
                int re = j;
                for (int l = 0, s = k; l < len; s = s / pl[l ++]) {
                    re -= s % pl[l];
                    if (re < 0) {
                        for (int d = 0, r = k; d < l; r = r / pl[d ++]) {
                            if ((r + 1) % pl[d]) {
                                add(h[k - tot[l] + tot[d]], h[k]);
                            }
                        }
                        break;
                    }
                }
            }
        }
        for (int j = 0; j < (1 << m); j ++) {
            int s = 0;
            for (int k = 0; k < m; k ++) {
                if (j >> k & 1) {
                    if (!~idn[k]) {
                        s = -1;
                        break;
                    }
                    s += tot[idn[k]];
                }
            }
            if (!~s) {
                w[j] = 0;
                continue;
            }
            w[j] = h[s];
            for (int k = 0, r = s; k < len; r = r / pl[k ++]) {
                for (int l = r % pl[k]; l; l --) {
                    w[j] = 1ll * l * w[j] % Mod;
                }
            }
        }
        for (int j = 0, step = 2; j < m; j ++, step = step << 1) {
            for (int lft = 0; lft < (1 << m); lft += step) {
                for (int rgt = 0; rgt < (1 << j); rgt ++) {
                    add(w[lft | (1 << j) | rgt], w[lft | rgt]);
                }
            }
        }
        for (int j = 0; j < (1 << m); j ++) {
            if (cnt[j] == i) {
                ans = (ans + 1ll * f[m][j] * w[j]) % Mod;
            }
        }
    }
    ans = (Mod + 1 - ans) % Mod;
    printf("%d\n", ans);
    return;
}

void solve() {
    init();
    calculate();
    return;
}

int main() {
    solve();
    return 0;
}