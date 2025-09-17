//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define fr front
# define il inline
# define fir first
# define sec second
# define vec vector
# define it iterator
# define pb push_back
# define lb lower_bound
# define ub upper_bound
# define all(x) x.begin(), x.end()
# define mem(a, b) memset(a, b, sizeof(a))

# define lc (t[p].l)
# define rc (t[p].r)
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r

# define sqr(x) ((x) * (x))
# define bpc __builtin_popcount
# define lowbit(x) ((x) & (-(x)))
# define geti(x, i) (((x) >> (i)) & 1)
# define set1(x, i) ((x) | (1 << (i)))
# define set0(x, i) ((x) & (~(1 << (i))))

# define debug1(x) cerr << #x << " = " << x << " "
# define debug2(x) cerr << #x << " = " << x << "\n"
# define bug cerr << "--------------------------\n"

# define each1(i, x) for(auto (i) : (x))
# define each2(i, x) for(auto (&i) : (x))
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
# define G(i, h, u, ne) for(int i = (h[(u)]); i; i = (ne[(i)]))
# define reps(i, a, b, c) for(int i = (a); i <= (b); i += (c))
# define pres(i, a, b, c) for(int i = (a); i >= (b); i -= (c))
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int N = 1e4 + 10;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int tp, n, m, k, lastans;
int c[N << 1], deep[N << 1];

vec<int> e[N << 1];

void dfs(int u){
	each2(v, e[u]){
		deep[v] = deep[u] + 1;
		dfs(v);
	}
}

void fcol(int u, int fa, int col){
	c[u] = (deep[u] - deep[fa] + col - 1) % k + 1;
	each2(v, e[u]){
		fcol(v, fa, col);
	}
}

int fcnt(int u, int col){
	int res = c[u] == col;
	each2(v, e[u]){
		res += fcnt(v, col);
	}
	
	return res;
}

signed main(){
# ifndef LOCAL
	freopen("grandiloquence.in", "r", stdin);
	freopen("grandiloquence.out", "w", stdout);
# endif
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> tp >> n >> m >> k;
	
	rep(i, 1, n){
		int x;
		cin >> x;
		if(x) e[x].pb(i);
	}
	
	dfs(1);
	
	int op, u, c;
	while(m --){
		cin >> op >> u;
		if(tp) u ^= lastans;
		if(op == 1){
			cin >> c;
			if(tp) c ^= lastans;
			fcol(u, u, c);
		}
		
		if(op == 2){
			cin >> c;
			if(tp) c ^= lastans;
			lastans = fcnt(u, c);
			cout << lastans << "\n";
		}
		
		if(op == 3){
			e[u].pb(++ n);
			deep[n] = deep[u] + 1;
		}
	}
	
	return 0;
}
/*
0
10 8 3
0 1 2 3 4 5 6 7 8 9
1 2 3
1 5 2
2 3 1
2 1 2
3 4
3 7
1 2 1
2 1 3

3
3
3
*/
/*
0
6 2 2
0 1 2 5 1 5
1 1 2
2 2 2

1
*/
