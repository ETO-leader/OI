#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 998'244'353;

ll modpow(ll a, ll e){
    ll r = 1;
    while(e){
        if(e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c;
    cin >> c;
    int n, m, k;
    if(!(cin >> n >> m >> k)) return 0;

    // read keys, skip (1,1) and (n,m) as in editorial
    vector<pair<int,int>> mids;
    for(int i=0;i<k;i++){
        int x,y; cin >> x >> y;
        if((x==1 && y==1) || (x==n && y==m)) continue;
        mids.emplace_back(x,y);
    }
    // sort middle keypoints by (x+y) then x then y
    sort(mids.begin(), mids.end(), [](const pair<int,int>&A, const pair<int,int>&B){
        int sa = A.first + A.second;
        int sb = B.first + B.second;
        if(sa != sb) return sa < sb;
        if(A.first != B.first) return A.first < B.first;
        return A.second < B.second;
    });

    // build full sequence a[1..K] (1-based idea):
    // a1 = (2,1), a2 = (1,2), then mids..., then (n,m-1), (n-1,m)
    vector<pair<int,int>> a;
    a.reserve(mids.size() + 4);
    a.emplace_back(2,1);           // index 1
    a.emplace_back(1,2);           // index 2
    for(auto &p: mids) a.push_back(p); // indices 3..(3+|mids|-1)
    a.emplace_back(n, m-1);        // next
    a.emplace_back(n-1, m);        // last

    int K = (int)a.size(); // equals original k + 4 (after skipping endpoints)

    // Precompute factorials up to n+m (safe bound)
    int LIM = n + m + 5;
    vector<ll> fac(LIM), ifac(LIM);
    fac[0] = 1;
    for(int i=1;i<LIM;i++) fac[i] = fac[i-1] * i % MOD;
    ifac[LIM-1] = modpow(fac[LIM-1], MOD-2);
    for(int i=LIM-2;i>=0;i--) ifac[i] = ifac[i+1] * (i+1) % MOD;
    auto C = [&](int A, int B)->ll{
        if(B < 0 || B > A) return 0;
        return fac[A] * ifac[B] % MOD * ifac[A-B] % MOD;
    };

    auto calc = [&](int p, int q)->ll {
        // p,q are 1-based indices in the editorial; our vector a is 0-based, so translate.
        auto [xp, yp] = a[p-1];
        auto [xq, yq] = a[q-1];
        int dx = xq - xp;
        int dy = yq - yp;
        if(dx < 0 || dy < 0) return 0;
        return C(dx + dy, dx);
    };

    // DP solve(p,q) as in editorial: p,q are 1-based indices (1 or 2)
    auto solve = [&](int p, int q)->ll{
        // dp is (K+1) x (K+1), 1-based indexing
        vector<vector<ll>> dp(K+1, vector<ll>(K+1, 0));
        dp[p][q] = 1;
        // iterate i from 3..K
        for(int i=3;i<=K;i++){
            for(int j=1;j<=i-2;j++){
                // four transitions from editorial
                dp[i-1][i] = (dp[i-1][i] + dp[i-1][j] * calc(j, i)) % MOD;
                dp[i][j]   = (dp[i][j]   + dp[i-1][j] * calc(i-1, i)) % MOD;
                dp[i][i-1] = (dp[i][i-1] + dp[j][i-1] * calc(j, i)) % MOD;
                dp[j][i]   = (dp[j][i]   + dp[j][i-1] * calc(i-1, i)) % MOD;
            }
        }
        for(auto&x:dp){
            for(auto&i:x) clog<<i<<' ';
            clog<<'\n';
        }
        return dp[K-1][K] - dp[K][K-1];
    };

    ll ans = (solve(1,2)) % MOD;
    if(ans < 0) ans += MOD;
    ans = ans * 2 % MOD;
    cout << ans << '\n';
    return 0;
}
