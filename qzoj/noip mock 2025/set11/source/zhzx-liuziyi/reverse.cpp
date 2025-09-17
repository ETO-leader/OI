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
constexpr int N=1000100;
struct BIT
{
	int n,tr[N];
	il void Clear(int _) { n=_; rep(i,1,n) tr[i]=0; }
	il void Add(int x,int z) { while(x<=n) tr[x]+=z,x+=x&(-x); }
	il int Sum(int x) { int s=0; while(x) s+=tr[x],x^=x&(-x); return s; }
};
BIT bit;
int n,a[N],b[N]; lr k;
il void Solve()
{
	cin>>n>>n>>k,bit.Clear(n);
	rep(i,1,n)
		cin>>a[i],b[i]=i-1-bit.Sum(a[i]),bit.Add(a[i],1);
	lr s=0;
	rep(i,1,n)
		s+=b[i];
	if(s==k)
		{ cout<<0<<'\n'; return; }
	lr ss=0; int r=0;
	bit.Clear(n);
	rep(l,1,n)
	{
		while(r<n&&ss<s-k)
			++r,ss+=r-l-bit.Sum(a[r]),bit.Add(a[r],1);
		if(ss==s-k)
			{ cout<<1<<'\n'<<l<<' '<<r<<'\n'; return; }
		ss-=bit.Sum(a[l]-1),bit.Add(a[l],-1);
	}
	lr sss=0;
	rep(i,1,n)
	{
		if(sss+b[i]>=s-k)
			{ cout<<2<<'\n'<<1<<' '<<i-1<<'\n'<<i-(s-k-sss)<<' '<<i<<'\n'; return; }
		sss+=b[i];
	}
}
int main()
{
	string fpre="reverse",isuf="in",osuf="out";
	assert(freopen((fpre+"."+isuf).c_str(),"r",stdin));
	assert(freopen((fpre+"."+osuf).c_str(),"w",stdout));
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T=1;
	while(T--)
		Solve();
	return 0;
}