//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline ll read(){
	char ch=getchar();ll x=0;int w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){return y<x?(x=y,1):0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){return x<y?(x=y,1):0;}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=1e6+5;
constexpr int maxm=5e3+5;
constexpr int mod=998244353;
constexpr int base=2137;
constexpr int V=1e9;
constexpr int H=18;
constexpr int W=64;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x<y)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
int Typ,n;
ll k;
int p[maxn];
int c[maxn];
void clear(){for(int i=1;i<=n;i++)c[i]=0;}
void add(int x,int k){for(;x<=n;x+=x&-x)c[x]+=k;}
int qry(int x){int s=0;for(;x;x-=x&-x)s+=c[x];return s;}
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	Typ=read(),n=read(),k=read();
	for(int i=1;i<=n;i++) p[i]=read();
	for(int i=n;i>=1;i--) k-=qry(p[i]),add(p[i],1);
	k=-k;
	if(!k) return cout<<0<<'\n',void();
	clear();
	ll cur=0;
	for(int r=1,l=1;r<=n;r++){
		cur+=r-l-qry(p[r]);
		add(p[r],1);
		while(l<=r&&cur>k) add(p[l],-1),cur-=qry(p[l]),l++;
		if(cur==k) return cout<<1<<'\n'<<l<<' '<<r<<'\n',void();
	}
	cout<<2<<'\n';
	clear();
	cur=0;
	for(int i=n;i>=1;i--){
		cur+=qry(p[i]);
		if(cur>k){
			cout<<i+1<<' '<<n<<'\n';
			cout<<i<<' '<<i+k-(cur-qry(p[i]))<<'\n';
			return;
		}
		add(p[i],1);
	}
}
bool Mem2;
signed main(){
	assert(freopen("reverse.in","r",stdin));
	assert(freopen("reverse.out","w",stdout));
	cin.tie(0),cout.tie(0);
	Init();int _=1;
	while(_--) Mymain();
	// cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	// cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
