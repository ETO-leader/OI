#include <bits/stdc++.h>
//#define FILE ""
#define INF 0x3f3f3f3f
#define INF_LL 0x3f3f3f3f3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int N = 4e5 + 5;

int n, m, k;

int col[N];

vector<int> vec[N];

void dfs(int u, int x) {
	if (x > k) {
		x = 1;
	}
	col[u] = x;
	for (int v : vec[u]) {
		dfs(v, x + 1);
	}
}
int get(int u, int x) {
	int res = (col[u] == x);
	for (int v : vec[u]) {
		res += get(v, x);
	}
	return res;
}

int main() {
	assert(freopen("grandiloquence.in", "r", stdin));
	assert(freopen("grandiloquence.out", "w", stdout));

	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int c;
	cin >> c;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		col[i] = -1;
	}
	for (int i = 1, x; i <= n; ++i) {
		cin >> x;
		vec[x].push_back(i);
	}
	int lst = 0;
	for (int i = 1; i <= m; ++i) {
		int op, u, x;
		cin >> op >> u;
		if ((c & 1) == 0) {
			u ^= lst;
		}
		if (op == 1) {
			cin >> x;
			if ((c & 1) == 0) {
				x ^= lst;
			}
			dfs(u, x);
		}
		else if (op == 2) {
			cin >> x;
			if ((c & 1) == 0) {
				x ^= lst;
			}
			cout << (lst = get(u, x)) << '\n';
		}
		else {
			col[++n] = -1;
			vec[u].push_back(n);
		}
	}

	return 0;
}