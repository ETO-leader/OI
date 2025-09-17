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
constexpr int maxn=2e3+5;
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
int n,m,k,ans;
vector<int> T[maxn];
int a[maxn];
void modify(int u,int d,int c){
	a[u]=(d+c-1)%k+1;
	for(int v:T[u]) modify(v,d+1,c);
}
int query(int u,int c){
	int s=(a[u]==c);
	for(int v:T[u]) s+=query(v,c);
	return s;
}
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) T[read()].push_back(i);
	while(m--){
		int op=read();
		if(op==1){
			int u=read(),c=read();
			if(Typ%2==0) u^=ans,c^=ans;
			modify(u,0,c);
		}else if(op==2){
			int u=read(),c=read();
			if(Typ%2==0) u^=ans,c^=ans;
			cout<<(ans=query(u,c))<<'\n';
		}else{
			int u=read();
			if(Typ%2==0) u^=ans;
			T[u].push_back(++n);
		}
	}
}
bool Mem2;
signed main(){
	assert(freopen("grandiloquence.in","r",stdin));
	assert(freopen("grandiloquence.out","w",stdout));
	cin.tie(0),cout.tie(0);
	Init();Typ=read();int _=1;
	while(_--) Mymain();
	// cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	// cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
