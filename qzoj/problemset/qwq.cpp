#include <bits/stdc++.h>
using namespace std;

typedef long long lld;

const int N = 107;
int T; lld n, mod;
lld ans;
int pr[N], tot, cnt[N];

bool isprime(int n)
{
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

lld qpow(lld a, lld n = mod)
{
    lld ret = 1;
    for (; n; n >>= 1, (a *= a) %= mod)
        if (n & 1)
            (ret *= a) %= mod;
    return ret;
}

void DFS(int i, lld tim, lld rc)
{
    clog << ">.< " << i << ' ' << tim << ' ' << rc << '\n';
    // cerr << i << '\n';
    if (i > tot)
    {
        (ans += qpow(2, tim) * rc) %= mod;
        return;
    }
    if (cnt[i] == 0)
    {
        DFS(i + 1, tim, rc);
    }
    else
    {
        DFS(i + 1, tim * (cnt[i] + 1), rc);
        DFS(i + 1, tim * (cnt[i] - 1), rc);
        DFS(i + 1, tim * cnt[i], (mod - 2 * rc % mod) % mod);
    }
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> T >> mod;
    for (int i = 2; i <= 100; ++i)
    {
        if (isprime(i))
        {
            pr[++tot] = i;
        }
    }
    for (int cas = 1; cas <= T; ++cas)
    {
        cin >> n;
        for (int i = 1; i <= tot; ++i)
        {
            int x = pr[i];
            cnt[i] = 0;
            while (n % x == 0)
            {
                ++cnt[i];
                n /= x;
            }
        }
        ans = 0;
        DFS(1, 1, 1);
        cout << ans << '\n';
    }
    // cout.flush();
    return 0;
}