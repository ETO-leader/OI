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
constexpr int N=100100;
string s,t; int n,m;
bitset<N> f,f0,f1,g[27];
il void Solve()
{
	cin>>s>>t,n=s.length(),m=t.length(),s=" "+s+" ",t=" "+t+" ";
	rep(i,1,26)
		g[i].reset();
	rep(i,1,n)
		g[s[i]^96][i]=1;
	f0.reset(),f1.reset(),f0[0]=1;
	int rgt=m; while(rgt>=2&&t[rgt]==t[rgt-1]) rgt-=2;
	rep(i,1,m)
	{
		if(i&1)
		{
			if(t[i]!=t[i-1]) f1=f=(f0<<1)&g[t[i]^96];
			else f1|=(f=(f0<<1)&g[t[i]^96]);
		}
		else
		{
			if(t[i]!=t[i-1]) f0=f=(f1<<1)&g[t[i]^96];
			else f0|=(f=(f1<<1)&g[t[i]^96]);
		}
		if(f[n]&&i>=rgt&&(~i^rgt)&1)
			{ cout<<"YES\n"; return; };
	}
	cout<<"NO\n";
}
int main()
{
	string fpre="string",isuf="in",osuf="out";
	assert(freopen((fpre+"."+isuf).c_str(),"r",stdin));
	assert(freopen((fpre+"."+osuf).c_str(),"w",stdout));
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int id,T; cin>>T>>id;
	while(T--)
		Solve();
	return 0;
}