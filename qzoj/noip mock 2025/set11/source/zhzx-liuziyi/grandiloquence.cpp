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
constexpr int N=400400,M=4040;
int id,n,m,k,rt,fa[N],dep[N],col[M]; vi v[N];
il void dfs(int u)
{
	for(int to:v[u])
		dep[to]=dep[u]+1,dfs(to);
}
il void dfs2(int u,int c)
{
	col[u]=c; int cc=(c==k)? 1:(c+1);
	for(int to:v[u])
		dfs2(to,cc);
}
il int dfs3(int u,int c)
{
	int ans=(col[u]==c);
	for(int to:v[u])
		ans+=dfs3(to,c);
	return ans;
}
il void Solve()
{
	cin>>id>>n>>m>>k;
	rep(i,1,n)
		cin>>fa[i],(!fa[i])&&(rt=i),v[fa[i]].eb(i);
	dfs(rt); int lst=0,nn=n;
	if(n<=2000&&m<=2000)
	{
		while(m--)
		{
			int op,x,y; cin>>op;
			if(op==1)
			{
				cin>>x>>y; if(id&1) x^=lst,y^=lst;
				dfs2(x,y);
			}
			if(op==2)
			{
				cin>>x>>y; if(id&1) x^=lst,y^=lst;
				cout<<(lst=dfs3(x,y))<<'\n';
			}
			if(op==3)
			{
				cin>>x; if(id&1) x^=lst;
				v[x].eb(++nn);
			}
		}
		return;
	}
}
int main()
{
	string fpre="grandiloquence",isuf="in",osuf="out";
	assert(freopen((fpre+"."+isuf).c_str(),"r",stdin));
	assert(freopen((fpre+"."+osuf).c_str(),"w",stdout));
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
	while(T--)
		Solve();
	return 0;
}