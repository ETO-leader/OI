//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define int LL
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

const int N = 1e6 + 10;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int sub, n, k;
int a[N], b[N], c[N];

LL rev[N];

namespace sub01{
	static int tr[N];
	void add(int x,int k){
		while(x<=n){
			tr[x]+=k;
			x+=(x&(-x));
		}
	}
	
	int query(int x){
		int res=0;
		while(x){
			res+=tr[x];
			x-=(x&(-x));
		}
		
		return res;
	}
	
	int check(int f[]){
		for(int i=0;i<=n;i++) tr[i]=0;
		int res=0;
		for(int i=n;i>=1;i--){
			res+=query(f[i]);
			add(f[i],1);
		}
		
		return res;
	}
	
	void solve(){
		if(check(a)==k){
			puts("0");
			return;
		}
		
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				for(int x=1;x<=n;x++) b[x]=a[x];
				sort(b+i,b+j+1);
				if(check(b)==k){
					puts("1");
					printf("%lld %lld\n",i,j);
					return;
				}
			}
		}
		
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				for(int x=1;x<=n;x++) b[x]=a[x];
				sort(b+i,b+j+1);
				for(int l=1;l<=n;l++){
					for(int r=l+1;r<=n;r++){
						for(int x=1;x<=n;x++) c[x]=b[x];
						sort(c+l,c+r+1);
						if(check(c)==k){
							puts("2");
							printf("%lld %lld\n",i,j);
							printf("%lld %lld\n",l,r);
							return;
						}
					}
				}
			}
		}
	}
}

namespace sub3{
	void solve(){
		cout << "0";
	}
}

namespace sub4{
	LL del;
	int x, s, t, ans;
	
	vec<PII> f;
	
	void solve(){
		del = (n - 1) * n / 2 - k;
		
		while(del){
			x = ub(rev + 1, rev + 1 + n + 1, del) - rev - 1;
			del -= rev[x];
			ans ++;
			s = 0;
			rep(i, 1, n){
				if(a[i] < a[i - 1]){
					if(!s) s = i - 1, t = i;
					else t ++;
				}
				
				else{
					if(s && t >= s + x - 1){
						t = s + x - 1;
						break;
					}
				}
			}
			
			if(t >= s + x - 1) t = s + x - 1;
			f.pb({s, t});
			reverse(a + s, a + t + 1);
		}
		
		cout << ans << "\n";
		
		each2(tmp, f){
			cout << tmp.fir << " " << tmp.sec << "\n";
		}
	}
}

signed main(){
# ifndef LOCAL
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
# endif
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> sub >> n >> k;
	
	rep(i, 1, n) cin >> a[i], rev[i] = (i - 1) * i / 2;
	rev[n + 1] = (n + 1) * n / 2;
	
	if(sub <= 1){
		sub01::solve();
		return 0;
	}
	
	if(sub == 3){
		sub3::solve();
		return 0;
	}
	
	if(sub == 4){
		sub4::solve();
		return 0;
	}
	
	return 0;
}
/*
4 7 7
7 6 5 4 3 2 1
*/
/*
1 11 16
4 1 9 10 11 3 5 6 7 2 8
1 12 4096
*/
