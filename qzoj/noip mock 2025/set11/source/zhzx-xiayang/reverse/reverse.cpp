#include <bits/stdc++.h>
//#define FILE ""
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 1e6 + 5;

int n, a[N];
ll k;

int tr[N];
void add(int k, int x) {
	for (; k <= n; k += (k & -k)) {
		tr[k] += x;
	}
}
int qry(int k) {
	int res = 0;
	for (; k; k ^= (k & -k)) {
		res += tr[k];
	}
	return res;
}

int main() {
	assert(freopen("reverse.in", "r", stdin));
	assert(freopen("reverse.out", "w", stdout));

	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int tp;
	cin >> tp >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	ll tot = 0;
	for (int i = n; i >= 1; --i) {
		tot += qry(a[i]);
		// cout << i << ' ' << qry(a[i]) << '\n';
		add(a[i], 1);
	}
	k = tot - k;

	if (!k) {
		cout << "0\n";
		return 0;
	}

	for (int i = 1; i <= n; ++i) {
		tr[i] = 0;
	}
	ll cur = 0;
	for (int l = 1, r = 1; r <= n; ++r) {
		cur += (r - l) - qry(a[r]);
		add(a[r], 1);
		for (; cur > k; ++l) {
			add(a[l], -1);
			cur -= qry(a[l]);
		}
		// cout << l << ' ' << r << ' ' << cur << '\n';
		if (cur == k) {
			cout << "1\n" << l << ' ' << r << '\n';
			return 0;
		}
	}

	for (int i = 1; i <= n; ++i) {
		tr[i] = 0;
	}
	cout << "2\n";
	for (int i = n; i >= 1; --i) {
		int tmp = qry(a[i]);
		if (tmp > k) {
			cout << i + 1 << ' ' << n << '\n';
			cout << i << ' ' << i + k << '\n';
			return 0;
		}
		add(a[i], 1);
		k -= tmp;
	}

	return 0;
}