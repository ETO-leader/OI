#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("trapv")
typedef long long ll;
const ll inf = 1e18;
const int MAXN = 4e5 + 25;
ll n, m, p;
ll s[MAXN];
array <int, 3> ee[MAXN];
ll P[MAXN], par[MAXN], ss[MAXN], sze[MAXN];
int find (int x) {
	return P[x] == x ? x : P[x] = find(P[x]);
}
ll tl[MAXN], tr[MAXN];
ll val[MAXN], v[MAXN];
ll dd2[MAXN];
pair <ll, ll> dp[MAXN];
ll o[MAXN];
void dfs (int pos) {
	v[pos] = ss[pos] * (val[pos] - val[par[pos]]);
	dd2[pos] = dd2[par[pos]] + v[pos];
	if (pos <= n) {
		dp[pos] = {v[pos], pos};
		o[pos] = v[pos];
		return;
	}
	dp[pos] = {ll(1e18), 0};
	dfs(tl[pos]); dfs(tr[pos]);
	dp[pos] = min(dp[pos], {dp[tl[pos]].first + v[pos], dp[tl[pos]].second});
	dp[pos] = min(dp[pos], {dp[tr[pos]].first + v[pos], dp[tr[pos]].second});
	o[dp[pos].second] = dd2[dp[pos].second] - dd2[par[pos]];;
}
void solve () {
	cin >> n >> m >> p;
	for (int i = 1; i <= p; i++) {
		cin >> s[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> ee[i][1] >> ee[i][2] >> ee[i][0];
	}
	sort(ee + 1, ee + m + 1);
	for (int i = 1; i <= 2 * n; i++) {
		o[i] = 0;
		P[i] = i; ss[i] = 0; sze[i] = 0; par[i] = 0; tl[i] = 0; tr[i] = 0; val[i] = 0;
	}
	for (int i = 1; i <= p; i++) {
		ss[s[i]] = 1;
	}
	for (int i = 1; i <= n; i++) {
		sze[i] = 1;
	}
	int cc = n;
	for (int i = 1; i <= m; i++) {
		int x = find(ee[i][1]), y = find(ee[i][2]);
		if (x == y) {
			continue;
		}
		cc++;
		val[cc] = ee[i][0];
		tl[cc] = x; tr[cc] = y;
		P[x] = cc; P[y] = cc;
		ss[cc] = ss[x] + ss[y];
		sze[cc] = sze[x] + sze[y];
		par[x] = cc; par[y] = cc;
	}
	dfs(2 * n - 1);
    for(auto c=1;c<n+1;++c) clog<<o[c]<<' ';
    clog<<'\n';
    for(auto c=1;c<n*2;++c) clog<<dd2[c]<<' ';
    clog<<'\n';
	sort(o + 1, o + n + 1);
	o[0] = o[n];
	// cout << o[0] << " ";
	// for (int i = 1; i < n; i++) {
	// 	o[i] += o[i - 1];
	// 	cout << o[i] << " ";
	// }
	// cout << '\n';
}				
signed main () {
    (cin.tie(nullptr)->sync_with_stdio(false));
	// #ifndef ONLINE_JUDGE 
	// 	freopen("input_file", "r", stdin);
	// 	freopen("output_file", "w", stdout);
	// #endif
	ios::sync_with_stdio(0); cin.tie(0);
	int tc = 1; cin >> tc;
	while (tc--) solve();
}
