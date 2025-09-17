#include <bits/stdc++.h>
using lint = long long;
using pii = std::pair<int, int>;

int T, subtaskid;
std::string a, b;
bool flg;
std::set<int> poses;

bool check() {
	std::string t;
	for (int i = 0; i < b.size(); ++i)
		if (poses.find(i) == poses.end()) t.push_back(b[i]);
	if (t.size() % 2 == 1) return false;
	for (int i = 1; i < b.size(); i += 2)
		if (t[i] != t[i - 1]) return false;
	return true;
}

void dfs(int u, int lst) {
	if (u == a.size()) {
		flg |= check();
		return ;
	}
	auto pos = b.find(a[u], lst + 1);
	while (pos != std::string::npos) {
		poses.emplace(pos);
		dfs(u + 1, pos);
		if (flg) return ;
		poses.erase(pos);
		pos = b.find(a[u], pos + 1);
	}
}

void solve() {
	poses.clear();
	std::cin >> a >> b, flg = false;
	dfs(0, -1);
	if (flg) std::cout << "YES\n";
	else std::cout << "NO\n";
}

int main() {
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	for (std::cin >> T >> subtaskid; T; --T) solve();
	std::cout.flush();
	return 0;
}
