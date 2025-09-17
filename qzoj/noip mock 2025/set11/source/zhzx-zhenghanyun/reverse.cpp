#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

ll id, n, k, sum, a[N];

struct BIT {
	int tree[N];

	inline int lowbit(int p) {
		return p & (-p);
	}

	inline void add(int p, int val) {
		while (p <= n) {
			tree[p] += val;
			p += lowbit(p);
		}
	}

	inline int get_sum(int p) {
		int res = 0;
		while (p) {
			res += tree[p];
			p ^= lowbit(p);
		}
		return res;
	}

	inline void clear() {
		memset(tree, 0, sizeof(tree));
	}
} T;

inline void check0() {
	for (int i = n; i; --i) {
		sum += T.get_sum(a[i]);
		T.add(a[i], 1);
	}
	if (sum == k) {
		cout << "0\n";
		exit(0);
	}
	T.clear();
}

inline void check1() {
	ll t = 0;
	for (int i = n, pos = n + 1; i; --i) {
		while (pos > 1 && t + k < sum) {
			--pos;
			t += T.get_sum(a[pos]);
			T.add(a[pos], 1);
		}
		if (t + k == sum) {
			cout << "1\n" << pos << " " << i << "\n";
			exit(0);
		}
		T.add(a[i], -1);
		t -= i - pos - T.get_sum(a[i]);
	}
	T.clear();
}

inline void check2() {
	ll t = 0;
	int pos = -1;
	for (int i = 1; i <= n; ++i) {
		T.add(a[i], 1);
		t += i - T.get_sum(a[i]);
		if (t + k > sum) {
			pos = i;
			break;
		}
	}
	cout << "2\n1 " << pos - 1 << "\n";
	sort(a + 1, a + pos);
	for (int i = 1; i <= pos; ++i) {
		if (a[i] > a[pos]) {
			--t;
		}
		if (t + k == sum) {
			cout << i + 1 << " " << pos << "\n";
			break;
		}
	}
}

int main() {
	assert(freopen("reverse.in", "r", stdin));
	assert(freopen("reverse.out", "w", stdout));
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> id >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	check0();
	check1();
	check2();
	return 0;
}