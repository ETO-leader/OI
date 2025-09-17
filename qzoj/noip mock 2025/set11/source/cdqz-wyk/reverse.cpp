#include <bits/stdc++.h>
#define LL long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define Let (u<<1)
#define Rit (u<<1|1)
#define lowbit(x) (x&(-x))
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 1e6 + 5;
int T, n, k, tot, a[maxn];
vector<pair<int, int > > v;
struct Bit1 {
	int val1[maxn];
	void clear() {
		memset(val1, 0, sizeof(val1));
		return ;
	}
	void update(int u, int w) {
		while (u) {
			val1[u] += w;
			u -= lowbit(u);
		}
		return ;
	}
	int query(int u) {
		int res = 0;
		while (u <= n) {
			res += val1[u];
			u += lowbit(u);
		}
		return res;
	}
} t1;
struct Bit2 {
	int val2[maxn];
	void clear() {
		memset(val2, 0, sizeof(val2));
		return ;
	}
	void update(int u, int w) {
		while (u <= n) {
			val2[u] += w;
			u += lowbit(u);
		}
		return ;
	}
	int query(int u) {
		int res = 0;
		while (u) {
			res += val2[u];
			u -= lowbit(u);
		}
		return res;
	}
} t2 ;
int solve() {
	int res = 0;
	t1.clear();
	for (int i = 1; i <= n; i++) {
		res += t1.query(a[i] + 1);
		t1.update(a[i], 1);
	}
	return res;
}
int main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	tot = solve();
	if (tot == k) {
		cout << 0 << '\n';
		return 0;
	}
	int T = 0;
	while (++T) {
		t1.clear(), t2.clear();
		int l = 1, r = 0, sum = 0, Max = -INF;
		pair<int, int > ans;
		for (l = 1; l <= n; l++) {
			while (r + 1 <= n) {
				int now = t1.query(a[r + 1] + 1);
				if (tot - sum - now >= k) {
					r++, sum += now;
					t1.update(a[r], 1);
					t2.update(a[r], 1);
					if (sum > Max) {
						Max = sum;
						ans = mp(l, r);
					}
				} else break;
			}
			sum -= t2.query(a[l] - 1);
			t1.update(a[l], -1);
			t2.update(a[l], -1);
		}
		v.pb(ans);
		sort(a + ans.fi, a + ans.se + 1);
		tot -= Max;
		if (tot == k) break;
	}
	cout << v.size() << '\n';
	for (auto now : v)
		cout << now.fi << ' ' << now.se << '\n';
	return 0;
}
