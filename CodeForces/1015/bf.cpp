#include <bits/stdc++.h>
using namespace std;
template <int P>
class mod_int
{
    using Z = mod_int;

private:
    static int mo(int x) { return x < 0 ? x + P : x; }

public:
    int x;
    int val() const { return x; }
    mod_int() : x(0) {}
    template <class T>
    mod_int(const T &x_) : x(x_ >= 0 && x_ < P ? static_cast<int>(x_) : mo(static_cast<int>(x_ % P))) {}
    bool operator==(const Z &rhs) const { return x == rhs.x; }
    bool operator!=(const Z &rhs) const { return x != rhs.x; }
    Z operator-() const { return Z(x ? P - x : 0); }
    Z pow(long long k) const
    {
        Z res = 1, t = *this;
        while (k)
        {
            if (k & 1)
                res *= t;
            if (k >>= 1)
                t *= t;
        }
        return res;
    }
    Z &operator++()
    {
        x < P - 1 ? ++x : x = 0;
        return *this;
    }
    Z &operator--()
    {
        x ? --x : x = P - 1;
        return *this;
    }
    Z operator++(int)
    {
        Z ret = x;
        x < P - 1 ? ++x : x = 0;
        return ret;
    }
    Z operator--(int)
    {
        Z ret = x;
        x ? --x : x = P - 1;
        return ret;
    }
    Z inv() const { return pow(P - 2); }
    Z &operator+=(const Z &rhs)
    {
        (x += rhs.x) >= P && (x -= P);
        return *this;
    }
    Z &operator-=(const Z &rhs)
    {
        (x -= rhs.x) < 0 && (x += P);
        return *this;
    }
    Z operator-() { return -x; }
    Z &operator*=(const Z &rhs)
    {
        x = 1ULL * x * rhs.x % P;
        return *this;
    }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                  \
    friend T operator o(const Z &lhs, const Z &rhs) \
    {                                               \
        Z res = lhs;                                \
        return res o## = rhs;                       \
    }
    setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
        friend istream &
        operator>>(istream &is, mod_int &x)
    {
        long long tmp;
        is >> tmp;
        x = tmp;
        return is;
    }
    friend ostream &operator<<(ostream &os, const mod_int &x)
    {
        os << x.val();
        return os;
    }
};
using Z = mod_int<1000000007>;
const int N = 5000;
Z fac[5020];
Z inv[5020];
Z C(int n, int i) { return n < 0 || i < 0 || n < i ? 0 : fac[n] * inv[i] * inv[n - i]; }
void solve()
{
    int n;
    cin >> n;
    int p[n] = {};
    for (int i = 0; i < n; i++)
        cin >> p[i];
    int pos[n] = {};
    memset(pos, -1, sizeof(pos));
    for (int i = 0; i < n; i++)
    {
        if (~p[i])
            pos[p[i]] = i;
    }
    int premn[n] = {};
    int premx[n] = {};
    premn[0] = ~pos[0] ? pos[0] : n;
    premx[0] = ~pos[0] ? pos[0] : -1;
    for (int i = 1; i < n; i++)
    {
        premn[i] = min(premn[i - 1], ~pos[i] ? pos[i] : n);
        premx[i] = max(premx[i - 1], ~pos[i] ? pos[i] : -1);
    }
    int lost[n] = {};
    for (int i = 0; i < n; i++)
        lost[i] = (!i ? 0 : lost[i - 1]) + (p[i] == -1);
    int have[n] = {};
    for (int i = 0; i < n; i++)
        have[i] = (!i ? 0 : have[i - 1]) + (pos[i] != -1);
    Z ans = 0;
    for (int l = 0; l < n; l++)
    {
        for (int r = l; r < n; r++)
        {
            int lostin = lost[r] - (!l ? 0 : lost[l - 1]);
            int lostout = lost[n - 1] - lostin;
            for (int mex = 1; mex <= n; mex++)
            {
                if (premn[mex - 1] < l || premx[mex - 1] > r)
                    continue;
                int need = mex - have[mex - 1];
                if (need > lostin)
                    continue;
                Z cnt = fac[lostout + (lostin - need)];
                ans += C(lostin, need) * fac[need] * cnt;
            }
        }
    }
    cout << ans << '\n';
}
int main()
{
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i;
    inv[N] = fac[N].inv();
    for (int i = N; i >= 1; i--)
        inv[i - 1] = inv[i] * i;
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}