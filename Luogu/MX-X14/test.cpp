#include<bits/stdc++.h>
#define pb push_back
#define popcnt __builtin_popcountll
#define debug printf("Passed line %d\n", __LINE__)

using namespace std;
typedef long long ll;
typedef vector<int> vint;
typedef pair<int, int> PII;

template<typename T> inline void read(T &x){
	x = 0; bool F = 0; char c = getchar();
	for (;!isdigit(c);c = getchar()) if (c == '-') F = 1;
	for (;isdigit(c);c = getchar()) x = x*10+(c^48);
	if (F) x = -x;
}

template<typename T1, typename... T2> inline void read(T1 &x, T2 &...y){read(x); read(y...);}

template<typename T> inline void checkmax(T &a, const T &b){if (a<b) a = b;}

template<typename T> inline void checkmin(T &a, const T &b){if (a>b) a = b;}

const int N = 4e5+5;
const ll MOD = 998244353;
unordered_map<int, int> ban[N];
int val[N], fa[N], n, m, k;
queue<int> q;
set<int> s;
ll ans;

inline ll qpow(ll x, ll y){
	ll ans = 1;
	while (y){
		if (y&1) (ans *= x) %= MOD;
		(x *= x) %= MOD, y >>= 1;
	}
	return ans;
}

int get_fa(int x){return fa[x] == x ? x : fa[x] = get_fa(fa[x]);}

void merge(int x, int y){
        clog<<"! "<<x-1<<' '<<y-1<<'\n';x = get_fa(x), y = get_fa(y); if (x!=y) fa[x] = y, val[y] ^= val[x], ans--;}

void dfs(int u){
    clog<<"!!! "<<u-1<<'\n';
	s.erase(u); int t = 0, up = 1e9;
	if (u<=n) t = n;
	else up = n;
	while (1){
		auto it = s.upper_bound(t);
		if (it == s.end()) break;
		t = *it;
		if (t>up) break;
		if (!ban[u].count(t)) dfs(t), merge(u, t);
	}
}

int main(){
	read(n, m, k); for (int i = 1;i<=n+m;i++) val[i] = 1, s.insert(i), fa[i] = i; ans = 1ll*n*m-k;
	int x, y, z; while (k--) read(x, y, z), y += n, val[x] ^= z, val[y] ^= z, ban[x][y] = ban[y][x] = 1;
	for (int i = 1;i<=n;i++) if (s.count(i)) dfs(i);
	for (int i = 1;i<=n+m;i++) if (val[get_fa(i)]) printf("0\n"), exit(0);
	printf("%lld\n", qpow(2, ans));
	return 0;
}