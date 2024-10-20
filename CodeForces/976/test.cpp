#include<bits/stdc++.h>
using namespace std;
using s64 = long long;
const s64 infl = 1e18;
const int inf = 2e9;
const int Mod = 1e9 + 7;
int mynorm(int x) {
    if (x < 0) {
        x += Mod;
    }
    if (x >= Mod) {
        x -= Mod;
    }
    return x;
}
template<class T>
T power(T a, s64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(mynorm(x)) {}
    Z(s64 x) : x(mynorm(x % Mod)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(mynorm(Mod - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, Mod - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = s64(x) * rhs.x % Mod;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = mynorm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = mynorm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        s64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

constexpr int MN = 31e6 + 35;
Z fac[MN], ifac[MN];
int n, k, d;
Z C(int n, int m) {
    return fac[n] * ifac[n - m] * ifac[m];
}
namespace min25 {
    const int M = 1E5 + 100;
    const int MOD = Mod;
    s64 B, N;

    // g(x)
    inline Z pg(int x) { return C(d + k, k); }
    // Sum[g(i),{x,2,x}]
    inline Z psg(s64 x) { return x * pg(0); }
    // f(pp=p^k)
    inline Z fpk(s64 p, s64 e, s64 pp) { return C(d + k * e, k * e); }
    
    inline s64 ph(s64 x) { return 1; }
    // Sum[g(i),{x,2,x}]
    inline s64 psh(s64 x) { return x % MOD - 1; }

    Z sg[M];
    s64 pr[M], pc, sh[M];
    void get_prime(s64 n) {
        static bool vis[M]; pc = 0;
        for (int i = 2; i < n + 1; i++) {
            if (!vis[i]) {
                pr[pc++] = i;
                sg[pc] = sg[pc - 1] + pg(i);
                sh[pc] = sh[pc - 1] + ph(i);
            }
            for(int j = 0; j < pc; j++) {
                if (pr[j] * i > n) break;
                vis[pr[j] * i] = 1;
                if (i % pr[j] == 0) break;
            }
        }
    }

    s64 w[M];
    s64 id1[M], id2[M], h[M];
    Z g[M];
    inline s64 id(s64 x) { return x <= B ? id1[x] : id2[N / x]; }

    Z go(s64 x, s64 k) {
        if (x <= 1 || (k >= 0 && pr[k] > x)) return 0;
        s64 t = id(x);
        Z ans = (g[t] - sg[k + 1]);
        for (int i = k + 1; i < pc; i++) {
            s64 p = pr[i];
            if (p * p > x) break;
            ans -= pg(p);
            // clog<<x<<' '<<k<<' '<<"qwq: "<<pg(p)<<' '<<ans<<" <= "<<p<<'\n';
            for (s64 pp = p, e = 1; pp <= x; ++e, pp = pp * p)
                ans += fpk(p, e, pp) * (1 + go(x / pp, i));
        }
        // clog<<x<<' '<<k+1<<' '<<ans<<'\n';
        return ans;
    }

    Z solve(s64 _N) {
        N = _N;
        B = sqrtl(N) + 7;
        get_prime(B);
        int sz = 0;

        for (s64 l = 1, v, r; l <= N; l = r + 1) {
            v = N / l; r = N / v;
            w[sz] = v;
            h[sz] = psh(v);
            if (v <= B) id1[v] = sz; else id2[r] = sz;
            sz++;
        }
        for (int k = 0; k < pc; k++) {
            s64 p = pr[k];
            for (int i = 0; i < sz; i++) {
                s64 v = w[i]; if (p * p > v) break;
                s64 t = id(v / p);
                h[i] = (h[i] - (h[t] - sh[k]) * ph(p)) % MOD;
            }
        }

        for (s64 l = 1, v, r; l <= N; l = r + 1) {
            v = N / l; r = N / v;
            g[id(v)] = psg(h[id(v)]);
        }

        // for (s64 l = 1, v, r; l <= N; l = r + 1) {
        //     v = N / l; r = N / v;
        //     cerr << v << ' ' << h[id(v)] << ' ' << g[id(v)] << '\n';
        //     cerr << pg(0) << '\n';
        // }
        return go(N, -1) + 1;
    }
}
void init(int n = 31e6) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
    ifac[n] = 1 / fac[n];
    for(int i = n; i; i--) ifac[i - 1] = ifac[i] * i;
}
void solve() {
    cin >> n >> k >> d;
    cout << min25::solve(n) << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr); cout.tie(nullptr);
    int TT = 1;
    init();
    cin >> TT;
    for( ;TT--; ) {
        solve();
    }
}
