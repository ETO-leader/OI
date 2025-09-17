#include <bits/stdc++.h>
using lint = long long;
using pii = std::pair<int, int>;
constexpr int N = 4e5 + 10;

std::vector<int> G[N];
int subtaskid, n, m, k, fa[N], c[N];

namespace subtask12 { // ±©Á¦

	void modify(int u, int x, int d) {
		c[u] = (d + x - 1) % k + 1;
		for (auto v : G[u])
			if (v != fa[u]) modify(v, x, d + 1);
	}
	
	int query(int u, int x) {
		int res = c[u] == x;
		for (auto v : G[u])
			if (v != fa[u]) res += query(v, x);
		return res;
	}

	void main() {
		for (int op, u, x; m; --m) {
			std::cin >> op >> u;
			if (op == 1) {
				std::cin >> x;
				modify(u, x, 0);
			} else if (op == 2) {
				std::cin >> x;
				std::cout << query(u, x) << "\n";
			} else {
				G[u].emplace_back(++n);
				G[n].emplace_back(u);
				fa[n] = u;
			}
		}
	}
};

int main() {
	freopen("grandiloquence.in", "r", stdin);
	freopen("grandiloquence.out", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> subtaskid >> n >> m >> k;
	for (int i = 1, f; i <= n; ++i) {
		std::cin >> f, fa[i] = f;
		if (i != 1) {
			G[f].emplace_back(i);
			G[i].emplace_back(f);
		}
	}
	subtask12::main();
//	if (subtaskid == 9 || subtaskid == 10) subtask910::main();
	std::cout.flush();
	return 0;
}
