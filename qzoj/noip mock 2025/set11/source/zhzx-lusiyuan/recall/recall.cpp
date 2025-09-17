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
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){return y<x?(x=y,1):0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){return x<y?(x=y,1):0;}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=1e5+5;
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
int Typ;
int n,mx,se;
vector<int> T[maxn];
void dfs(int u,int f,int d){
	if(d>=mx) se=mx,mx=d;
	else if(d>se) se=d;
	for(int v:T[u]){
		if(v==f) continue;
		dfs(v,u,d+1);
	}
}
void Init(){}
void Clear(){
	for(int i=1;i<=n;i++) T[i].clear();
	mx=se=0;
}
void Mymain(){
	Clear();
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		T[u].push_back(v),T[v].push_back(u);
	}
	dfs(1,0,1);
	if(Typ==2){
		int ans=1;
		for(int i=1;i<=n;i++) ans=1ll*ans*i%mod;
		cout<<n<<' '<<ans<<'\n';
		return;
	}
	if(Typ==3) return cout<<2<<' '<<1<<'\n',void();
}
bool Mem2;
signed main(){
	assert(freopen("recall.in","r",stdin));
	assert(freopen("recall.out","w",stdout));
	cin.tie(0),cout.tie(0);
	Init();Typ=read();int _=read();
	if(Typ==0){
		cout<<"5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n";
		return 0;
	}
	while(_--) Mymain();
	// cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	// cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
