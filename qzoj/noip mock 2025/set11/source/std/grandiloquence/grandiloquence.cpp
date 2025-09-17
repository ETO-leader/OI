#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for (int i = a; i <= b; ++i)
#define Ford(i, a, b) for (int i = a; i >= b; --i)

const int maxN = 4e5+7;
const int maxK = 17;

int n, m, k;

namespace Splay
{
	const int T = 8e5+7;
	
	int s[T][2], fa[T];
	int self[T];
	int col[T][maxK];
	int cnt[T][maxK];
	int dep[T];
	int tag[T];
	int tot;
	
#define ls(v) s[v][0]
#define rs(v) s[v][1]
	int allocate() { return ++tot; }
	int newNode(int d)
	{
		int v = allocate();
		ls(v) = rs(v) = 0;
		self[v] = -1;
		dep[v] = d % k;
		memset(col[v], 0, sizeof(col[v]));
		memset(cnt[v], 0, sizeof(cnt[v]));
		cnt[v][d % k] = 1;
		tag[v] = -1;
		return v;
	}
	void pushUp(int v)
	{
		For (i, 0, k - 1)
		{
			col[v][i] = col[ls(v)][i] + col[rs(v)][i];
			cnt[v][i] = cnt[ls(v)][i] + cnt[rs(v)][i];
		}
		if (self[v] != -1) ++col[v][self[v]];
		++cnt[v][dep[v]];
	}
	void update(int v, int x)
	{
		if (!v || x == -1) return;
		self[v] = (dep[v] + x) % k;
		tag[v] = x;
		For (i, 0, k - 1) col[v][(i + x) % k] = cnt[v][i];
	}
	int getDir(int v) { return rs(fa[v]) == v; }
	void rotate(int v)
	{
		int fv = fa[v], ffv = fa[fv], c = getDir(v);
		if (ffv) s[ffv][getDir(fv)] = v;
		s[fv][c] = s[v][!c], fa[s[v][!c]] = fv;
		s[v][!c] = fv, fa[fv] = v;
		fa[v] = ffv;
		pushUp(fv), pushUp(v);
	}
	void pushDown(int v)
	{
		update(ls(v), tag[v]), update(rs(v), tag[v]);
		tag[v] = -1;
	}
	void PD(int v)
	{
		if (fa[v]) PD(fa[v]);
		pushDown(v);
	}
	void splay(int v, int root = 0)
	{
		PD(v);
		while (fa[v] != root)
		{
			if (fa[fa[v]] != root)
				rotate(getDir(v) == getDir(fa[v]) ? fa[v] : v);
			rotate(v);
		}
	}
	
	void printRoot(int v)
	{
		if (!v) return;
		pushDown(v);
		printRoot(ls(v));
//		fprintf(stderr, "%d ", self[v]);
		printRoot(rs(v));
	}
	void print()
	{
		splay(1);
		printRoot(1);
//		fprintf(stderr, "\n");
	}
}

namespace WORK
{
	int lb[maxN], rb[maxN], lst[maxN];
	int depth[maxN];
	
	void mdfSeg(int u, int c)
	{
		using namespace Splay;
		splay(lb[u]);
		splay(rb[u], lb[u]);
		int x = ((c - depth[u]) % k + k) % k;
		update(ls(rb[u]), x);
		self[rb[u]] = (dep[rb[u]] + x) % k;
		pushUp(rb[u]);
		self[lb[u]] = (dep[lb[u]] + x) % k;
		pushUp(lb[u]);
	}
	void setFa(int u, int f)
	{
		using namespace Splay;
		splay(lst[f]);
		splay(rb[f], lst[f]);
		// assert(!ls(rb[f]));
		ls(rb[f]) = lb[u];
		fa[lb[u]] = rb[f];
		pushUp(rb[f]);
		pushUp(lst[f]);
		lst[f] = rb[u];
	}
	void setNode(int u)
	{
		using namespace Splay;
		lb[u] = newNode(depth[u] % k);
		rb[u] = newNode(depth[u] % k);
		// assert(dep[lb[u]] == dep[rb[u]]);
		lst[u] = lb[u];
		rs(lb[u]) = rb[u];
		fa[rb[u]] = lb[u];
		pushUp(lb[u]);
	}
	int qrySeg(int u, int c)
	{
		using namespace Splay;
		splay(lb[u]);
		// fprintf(stderr, "splay1 ended\n");
		splay(rb[u], lb[u]);
		// fprintf(stderr, "splay2 ended\n");
		int ret = col[ls(rb[u])][c];
		// assert(ret % 2 == 0);
		// fprintf(stderr, "ret = %d\n", ret);
		// fprintf(stderr, "%d %d\n", self[lb[u]], self[rb[u]]);
		ret += self[lb[u]] == c;
		ret += self[rb[u]] == c;
		return ret;
	}
	
	vector<int> son[maxN];
	void DFS(int u)
	{
		for (int v : son[u])
		{
			depth[v] = (depth[u] + 1) % k;
			setNode(v);
			setFa(v, u);
			DFS(v);
		}
	}
	
	void main()
	{
		int tp;
		scanf("%d", &tp);
		scanf("%d%d%d", &n, &m, &k);
		// scanf("%*d");
		int root = 1;
		For (i, 1, n)
		{
			// fprintf(stderr, "in %d\n", i);
			int x; scanf("%d", &x);
			son[x].push_back(i);
			if (!x) root = i;
		}
		setNode(root);
		DFS(root);
		Splay::splay(lb[1]);
		// For (i, 0, k - 1) fprintf(stderr, "%d%c", Splay::cnt[lb[1]][i] / 2, " \n"[i == k - 1]);
		int lstans = 0;
		int cnt=0;
		For (cas, 1, m)
		{
			// fprintf(stderr, "case:%d\n", cas);
			int opt; scanf("%d", &opt);
			if (opt == 1)
			{
				int u, c; scanf("%d%d", &u, &c);
				if(tp%2==0)u^=lstans, c^=lstans;
				c %= k;
				mdfSeg(u, c);
			}
			if (opt == 2)
			{
				int u, c; scanf("%d%d", &u, &c);
				if(tp%2==0)u^=lstans, c^=lstans;
				c %= k;
				int ret = qrySeg(u, c);
				lstans = ret/2;
				assert(ret % 2 == 0);
				
				printf("%d\n", lstans);
			}
			if (opt == 3)
			{
				int x; scanf("%d", &x);
				if(tp%2==0)x^=lstans;
				int v = ++n;
				depth[v] = (depth[x] + 1) % k;
				setNode(v);
				setFa(v, x);
			}
			// Splay::print();
		}
	}
}

int main()
{
	freopen("grandiloquence.in", "r", stdin);
	freopen("grandiloquence.out", "w", stdout);
//	freopen("code", "w", stdout);
	WORK::main();
	return 0;
}
