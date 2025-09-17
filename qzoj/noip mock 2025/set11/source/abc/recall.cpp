#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
constexpr int maxn = 100000 + 10;
constexpr int len = 340;
constexpr int siz = 1570;
struct bitst{
    u64 a[siz];
    void reset(){
        memset(a, 0, sizeof(a));
    }
    void set(int x){
        a[(x >> 6)] |= 1ull << (x & 63);
    }
    void flip(int x){
        a[(x >> 6)] ^= 1ull << (x & 63);
    }
    void operator|=(const bitst &b){
        for (int i=0;i<siz;++i) a[i] |= b.a[i];
    }
    void operator^=(const bitst &b){
        for (int i=0;i<siz;++i) a[i] ^= b.a[i];
    }
    void operator&=(const bitst &b){
        for (int i=0;i<siz;++i) a[i] &= b.a[i];
    }
    int val(int x){
        return a[x >> 6] >> (x & 63) & 1;
    }
};
bitst G[maxn];
bitst A[len], B[len];
vector<int> e[maxn];
#define lt(x) (!(x) ? 1 : (x) * len)
#define rt(x) (min(((x) * len + len - 1), n))
int a[maxn], b[maxn];
int ia[maxn], ib[maxn];
int n, m, q;
int idx;
void solve(){
    cin >> n >> m >> q;
    for (int i=1;i<=n;++i) e[i].clear();
    for (int i=1;i<=m;++i){
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
    }
    for (int i=n;i>=1;--i){
        G[i].reset();
        G[i].set(i);
        for (int v : e[i]) G[i] |= G[v];
    }
    int k = 0;
    while (lt(k) <= n) ++k;
    for (int i=0;i<=k;++i) A[i].reset(), B[i].reset();
    for (int i=1;i<=n;++i) cin >> a[i], ia[a[i]] = i;
    for (int i=1;i<=n;++i) cin >> b[i], ib[b[i]] = i;
    for (int i=1;i<=n;++i) A[a[i] / len].set(i), B[b[i] / len].set(i);
    for (int i=k-2;i>=0;--i) A[i] |= A[i + 1], B[i] |= B[i + 1];
    while (q--){
        int o;
        cin >> o;
        if (o == 1){
            int x, y;
            cin >> x >> y;
            int l = a[x] / len, r = a[y] / len;
            if (l > r) swap(l, r);
            for (int i=l+1;i<=r;++i) A[i].flip(x), A[i].flip(y);
            swap(a[x], a[y]);
            swap(ia[a[x]], ia[a[y]]);
        }
        else if (o == 2){
            int x, y;
            cin >> x >> y;
            int l = b[x] / len, r = b[y] / len;
            if (l > r) swap(l, r);
            for (int i=l+1;i<=r;++i) B[i].flip(x), B[i].flip(y);
            swap(b[x], b[y]);
            swap(ib[b[x]], ib[b[y]]);
        }
        else{
            int x, l, r;
            cin >> x >> l >> r; ++r;
            int y = (r + len - 1) / len;
            bitst u = A[y];
            y = min(n + 1, len * y);
            for (int i=r;i<y;++i) u.set(ia[i]);
            y = (l + len - 1) / len;
            u ^= A[y];
            y = min(n + 1, len * y);
            for (int i=l;i<y;++i) u.flip(ia[i]);
            u &= G[x];
            int p = 0;
            for (int i=0;i<siz&&p<k-1;++i){
                while (u.a[i] & B[p + 1].a[i]) ++p;
            }
            l = lt(p); r = rt(p);
            int ans = 0;
            for (int i=r;i>=l;--i) if (u.val(ib[i])){
                ans = i;
                break;
            }
            cout << ans << '\n';
        }
    }
}
int main(){
    int c, t;
    cin >> c >> t;
    while (t--) solve();
    return 0;
}


