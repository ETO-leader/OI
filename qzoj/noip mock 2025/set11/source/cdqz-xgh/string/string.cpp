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

const int N = 1e5 + 10;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int T, sub, l1, l2;
char s[N], t[N];

namespace sub123{
	const int M = 2e3 + 10;
	bitset<M> dp[M];
	
	void solve(){
		while(T --){
			cin >> s + 1 >> t + 1;
			l1 = strlen(s + 1), l2 = strlen(t + 1);
			
			rep(i, 0, l1) dp[i].reset();
			
			if((l2 - l1) & 1){
				cout << "NO\n";
				continue;
			}
			
			dp[0][0] = true; 
			rep(i, 0, l1){
				rep(j, 1, l2){
					if(s[i] == t[j]) dp[i][j] = dp[i][j] | dp[i - 1][j - 1];
					if(j >= 2 && t[j] == t[j - 1]) dp[i][j] = dp[i][j] | dp[i][j - 2];
				}
			}
			
			if(dp[l1][l2]) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	
}

namespace sub5{
	const int M = 30;
	bitset<N> dp[M];
	
	void solve(){
		while(T --){
			cin >> s + 1 >> t + 1;
			l1 = strlen(s + 1), l2 = strlen(t + 1);
			
			rep(i, 0, l1) dp[i].reset();
			
			if((l2 - l1) & 1){
				cout << "NO\n";
				continue;
			}
			
			dp[0][0] = true; 
			rep(i, 0, l1){
				rep(j, 1, l2){
					if(s[i] == t[j]) dp[i][j] = dp[i][j] | dp[i - 1][j - 1];
					if(j >= 2 && t[j] == t[j - 1]) dp[i][j] = dp[i][j] | dp[i][j - 2];
				}
			}
			
			if(dp[l1][l2]) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}

namespace sub6{
	void solve(){
		while(T --){
			cin >> s + 1 >> t + 1;
			l1 = strlen(s + 1), l2 = strlen(t + 1);
			if((l2 - l1) & 1) cout << "NO\n";
			else cout << "YES\n";
		}
	}
}

signed main(){
# ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
# endif
//	freopen("string3.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> T >> sub;
	
	if(sub <= 3){
		sub123::solve();
		return 0;
	}
	
	if(sub == 5){
		sub5::solve();
		return 0;
	}
	
	if(sub == 6){
		sub6::solve();
		return 0;
	}
	
	return 0;
}
/*
2 1
hllo
haalbblocc
hllo
habballocc

YES
NO
*/
/*
1 1
llrllrll
llllllrlllrrlllrllaabbccdd

YES
*/
