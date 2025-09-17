#include <bits/stdc++.h>
using lint = long long;
using pii = std::pair<int, int>;
constexpr int N = 1e6 + 10;

lint k;
std::vector<int> arr;
int subtaskid, n, a[N];

struct SegmentTree {
	int sum[N];
	
	void pushup(int u) {
		sum[u] = sum[u << 1] + sum[u << 1 | 1];
	}
	
	void add(int u, int l, int r, int pos, int x) {
		if (l == r) return sum[u] += x, void();
		int mid = l + r >> 1;
		if (pos <= mid) add(u << 1, l, mid, pos, x);
		else add(u << 1 | 1, mid + 1, r, pos, x);
		pushup(u);
	}
	
	int ask(int u, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (ql <= l && r <= qr) return sum[u];
		int mid = l + r >> 1;
		if (qr <= mid) return ask(u << 1, l, mid, ql, qr);
		if (ql > mid) return ask(u << 1 | 1, mid + 1, r, ql, qr);
		return ask(u << 1, l, mid, ql, qr) + ask(u << 1 | 1, mid + 1, r, ql, qr);
	}
};

lint countInversions(const std::vector<int>& a) {
  int n = a.size();
  std::vector<int> bit(n + 2, 0);
  auto add = [&](int x) {
    for (; x <= n; x += x & -x) bit[x]++;
  };
  auto sum = [&](int x) {
    int s = 0;
    for (; x > 0; x -= x & -x) s += bit[x];
    return s;
  };
  lint inv = 0;
  for (int i = n - 1; i >= 0; i--) {
    inv += sum(a[i] - 1);
    add(a[i]);
  }
  return inv;
}

namespace subtask3 {
	void main() {
		std::cout << 0 << std::endl;
	}
}

namespace subtask5 {
	SegmentTree T;
	
	void main() {
		lint target = countInversions(arr) - k;
		lint t = 0;
		for (int l = 1, r = 0; l <= n; ++l) {
			while (r < n && t < target) {
				T.add(1, 1, n, a[++r], 1);
				t += T.ask(1, 1, n, a[r] + 1, n);
				if (t >= target) break;
			}
			if (t == target) {
				std::cout << "1\n" << l << " " << r << "\n";
				return ;
			}
			t -= T.ask(1, 1, n, 1, a[l] - 1);
			T.add(1, 1, n, a[l], -1);
		}
	}
}

namespace subtask0 {
	std::vector<pii> ans;
	int p;
	bool flg;
	
	std::set<pii> ranges;
	
	bool test() {
		std::vector<int > qwq(arr);
		for (auto t : ranges) {
			std::sort(qwq.begin() + t.first - 1, qwq.begin() + t.second);
		}
		if (countInversions(qwq) == k) return true;
		return false;
	}
	
	void dfs(int u) { // 考虑第 u 个区间 
		if (u == p + 1) {
			if (test()) {
				flg = true;
				ans.clear();
				for (auto x : ranges) ans.emplace_back(x);
			}
			return ;
		}
		for (int l = 1; l <= n; ++l) {
			for (int r = l ; r <= n; ++r) {
				if (ranges.find({l, r}) == ranges.end()) {
					ranges.insert({l, r});
					dfs(u + 1);
					if (flg) return ;
					ranges.erase({l, r});
				}
			}
		}
	}
	
	bool check() {
		flg = false;
		dfs(1);
		return flg;
	}
	
	void main() {
		for (p = 1; p <= 7; ++p) {
			if (check()) {
				std::cout << p << "\n";
				for (auto x : ans) std::cout << x.first << " " << x.second << "\n";
				return ;
			}
		}		
	}
}

int main() {
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> subtaskid >> n >> k;
	for (int i = 1; i <= n; ++i) std::cin >> a[i], arr.emplace_back(a[i]);
	if (countInversions(arr) == k) {
		std::cout << 0 << std::endl;
		return 0;
	}
	if (subtaskid == 0) {
		subtask0::main();
		return 0;
	}
	subtask5::main();
	std::cout.flush();
	return 0;
}
