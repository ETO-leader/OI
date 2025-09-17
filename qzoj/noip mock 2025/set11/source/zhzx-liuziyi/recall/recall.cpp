#include<bits/stdc++.h>
using namespace std;
#define il inline
#define fi first
#define se second
#define mk make_pair
#define eb emplace_back
#define rep(i,l,r) for(int i=(l); i<=(r); ++i)
#define rep_(i,l,r) for(int i=(l); i>=(r); --i)
typedef unsigned U;
typedef long long lr;
typedef unsigned long long ull;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
constexpr int mod1=998244353,mod2=1e9+7;
constexpr db pi=3.141592653589793,eps=1e-9;
constexpr int inf32=0x3f3f3f3f,Inf32=0xc0c0c0c0;
constexpr lr inf64=0x3f3f3f3f3f3f3f3f,Inf64=0xc0c0c0c0c0c0c0c0;
template<typename T>il T Max(T x,T y) { return (x>y)? x:y; }
template<typename T>il T Min(T x,T y) { return (x<y)? x:y; }
template<typename T>il T gcd(T x,T y) { return (!y)? x:gcd(y,x%y); }
template<typename T>il T Abs(T x) { return (x>0)? x:(-x); }
template<typename T>il T Rnd(T l,T r,mt19937_64 &eng)
{
	uniform_int_distribution<T> uid(l,r);
	return uid(eng);
}
mt19937_64 eng(chrono::high_resolution_clock::now().time_since_epoch().count());
using Int=const int&;
constexpr int N=100100,M=105,mod=mod1;
il void Reduce(int &_) { (_>=mod)&&(_-=mod); }
int n,m,dep[N],son[N],dep2[N],a[M],c[M][M],g[M][M],f[M][M][M]; vi v[N];
il void dfs(int u,int fa)
{
	dep[u]=1,dep2[u]=0;
	for(int to:v[u])
		if(to!=fa)
		{
			dfs(to,u);
			if(dep[to]+1>=dep[u])
				dep[u]=dep[to]+1,son[u]=to;
		}
	for(int to:v[u])
		if(to!=fa&&to!=son[u])
			dep2[u]=Max(dep2[u],dep[to]);
}
il void Solve()
{
	cin>>n;
	rep(i,1,n)
		v[i].clear();
	rep(i,1,n-1)
	{
		int x,y; cin>>x>>y;
		v[x].eb(y),v[y].eb(x);
	}
	dfs(1,0),cout<<(m=dep[1])<<' ';
	int pos=1;
	rep(i,1,m)
		a[i]=dep2[pos],pos=son[pos];
	rep(i,0,m)
	{
		c[i][0]=1;
		rep(j,1,i)
			Reduce(c[i][j]=c[i-1][j]+c[i-1][j-1]);
	}
	rep(i,1,m)
		rep(j,i,m)
			g[i][j]=Max(g[i][j-1],a[j]+j);
	memset(f,0,sizeof(f));
	rep(i,1,m+1)
		rep(j,0,m+1)
			f[i][i-1][j]=1;
	rep(t,1,m)
		rep(l,1,m-t+1)
		{
			int r=l+t-1;
			rep_(k,m,0)
			{
				if(g[l][r]-k>r)
					continue;
				rep(p,l,r)
					f[l][r][k]=(f[l][r][k]+(ull)f[l][p-1][k]*f[p][r-1][k+1]%mod*c[r-l][p-l])%mod;
			}
		}
	cout<<f[1][m][0]<<'\n';
}
int main()
{
	string fpre="recall",isuf="in",osuf="out";
	assert(freopen((fpre+"."+isuf).c_str(),"r",stdin));
	assert(freopen((fpre+"."+osuf).c_str(),"w",stdout));
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T; cin>>T>>T;
	while(T--)
		Solve();
	return 0;
}