#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());

const int N = 4e5 + 5;
const int B = 640;

int o, n, m, k, cnt, ans, fa[N], dep[N];

vector<int> E[N];

struct T {
	int a[10];

	T() { memset(a, 0, sizeof(a)); }

	inline int &operator[](const int &p) {
		return a[p];
	}

	inline T operator+(const T &rhs) const {
		T res;
		for (int i = 0; i < 10; ++i) {
			res.a[i] = a[i] + rhs.a[i];
		}
		return res;
	}
};

struct node {
	T vdep, vcol; int lson, rson, fa, siz, dep, col, tag; ull prio;
} t[N];

inline void pushup(int i) {
	int ls = t[i].lson, rs = t[i].rson;
	t[ls].fa = t[rs].fa = i;
	t[i].siz = t[ls].siz + t[rs].siz + 1;
	t[i].vcol = t[ls].vcol + t[rs].vcol;
	t[i].vdep = t[ls].vdep + t[rs].vdep;
	if (t[i].col != -1) {
		++t[i].vcol[t[i].col];
	}
	++t[i].vdep[t[i].dep];
}

inline void modify(T &x, const T &y, int c) {
	for (int i = 0; i < k; ++i) {
		x.a[(i + c) % k] = y.a[i];
	}
}

inline void modify(int i, int c) {
	t[i].col = (t[i].dep + c) % k;
	modify(t[i].vcol, t[i].vdep, c);
	t[i].tag = c;
}

inline void pushdown(int i) {
	if (t[i].tag == -1) {
		return;
	}
	modify(t[i].lson, t[i].tag);
	modify(t[i].rson, t[i].tag);
	t[i].tag = -1;
}

inline void split(int i, int k, int &x, int &y) {
	if (!i) {
		x = y = 0;
		return;
	}
	pushdown(i);
	if (t[t[i].lson].siz < k) {
		split(t[i].rson, k - t[t[i].lson].siz - 1, t[i].rson, y);
		x = i;
	} else {
		split(t[i].lson, k, x, t[i].lson);
		y = i;
	}
	pushup(i);
}

inline int merge(int x, int y) {
	if (!x || !y) {
		return x | y;
	}
	if (t[x].prio < t[y].prio) {
		pushdown(x);
		t[x].rson = merge(t[x].rson, y);
		pushup(x);
		return x;
	} else {
		pushdown(y);
		t[y].lson = merge(x, t[y].lson);
		pushup(y);
		return y;
	}
}

int root;

inline int new_node(int u) {
	t[u].vdep[dep[u]] = 1;
	t[u].siz = 1;
	t[u].dep = dep[u];
	t[u].col = -1;
	t[u].tag = -1;
	t[u].prio = rng();
	return u;
}

inline void dfs0(int u) {
	dep[u] = (dep[fa[u]] + 1) % k;
	root = merge(root, new_node(u));
	for (auto v: E[u]) {
		dfs0(v);
	}
}

bitset<N> vis;
vector<int> vec;

inline void split(int i, int &x, int &y) {
	if (!i) {
		x = y = 0;
		return;
	}
	if (!vis[i]) {
		x = i, y = 0;
		return;
	}
	pushdown(i);
	if (vis[t[i].rson]) {
		split(t[i].rson, t[i].rson, y);
		x = i;
	} else {
		split(t[i].lson, x, t[i].lson);
		y = i;
	}
	pushup(i);
}

inline void split_by_val(int u, int &x, int &y) {
	int v = u;
	while (1) {
		vec.emplace_back(v);
		vis[v] = 1;
		if (v == root) {
			break;
		}
		v = t[v].fa;
	}
	split(root, x, y);
	for (auto v: vec) {
		vis[v] = 0;
	}
	vec.clear();
}

struct BIT {
	int tree[N];

	inline int lowbit(int p) {
		return p & (-p);
	}

	inline void add(int p, int val) {
		while (p <= n + m) {
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

	inline int query(int l, int r) {
		return get_sum(r) - get_sum(l - 1);
	}

	inline void clear() {
		memset(tree, 0, sizeof(tree));
	}
} X;

int dfn[N], siz[N], maxs[N], dfntot;

inline void dfs1(int u) {
	maxs[u] = 0;
	dfn[u] = ++dfntot;
	siz[u] = 1;
	for (auto v: E[u]) {
		dfs1(v);
		siz[u] += siz[v];
	}
}

int la;

inline int get_siz(int u) {
	if (u <= la) {
		return siz[u] + X.query(dfn[u], dfn[u] + siz[u] - 1);
	}
	return siz[u];
}

inline void build() {
	dfntot = 0;
	dfs1(1);
	X.clear();
	la = cnt;
}

int main() {
	assert(freopen("grandiloquence.in", "r", stdin));
	assert(freopen("grandiloquence.out", "w", stdout));
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> o >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> fa[i];
		E[fa[i]].emplace_back(i);
	}
	dfs0(1);
	cnt = n;
	la = n;
	build();
	while (m--) {
		int op, u, c = 0;
		cin >> op >> u;
		if (op != 3) {
			cin >> c;
		}
		if (o & 1) {
			u ^= ans, c ^= ans;
		}
		bool rebuild = 0;
		if (op == 1) {
			c = (c - dep[u] % k + k) % k;
			int x = 0, y = 0, z = 0;
			split_by_val(u, x, y);
			split(y, get_siz(u), y, z);
			modify(y, c);
			root = merge(merge(x, y), z);
		} else if (op == 2) {
			c %= k;
			int x = 0, y = 0, z = 0;
			split_by_val(u, x, y);
			split(y, get_siz(u), y, z);
			cout << (ans = t[y].vcol[c]) << "\n";
			root = merge(merge(x, y), z);
		} else {
			fa[++cnt] = u;
			dep[cnt] = (dep[u] + 1) % k;
			E[u].emplace_back(cnt);
			int x = 0, y = 0, z = 0;
			split_by_val(u, x, y);
			split(y, 1, y, z);
			root = merge(merge(x, (merge(y, new_node(cnt)))), z);
			maxs[cnt] = maxs[u] + 1;
			if (maxs[cnt] > B) {
				rebuild = 1;
			}
			u = cnt;
			while (u > la) {
				++siz[u], u = fa[u];
			}
			X.add(dfn[u], 1);
		}
		if (rebuild) {
			build();
		}
	}
	return 0;
}