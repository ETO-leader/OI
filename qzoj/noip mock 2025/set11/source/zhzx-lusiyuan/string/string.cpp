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
constexpr int maxn=2e4+5;
constexpr int maxm=1e5+5;
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
int n,m;
string a,b;
bitset<maxn> dp[maxn];
bitset<maxn> tra[Z];
void solve1234(){
	dp[0][0]=1;
	for(int i=1;i<=n;i++) tra[a[i]-'a'][i]=1;
	for(int i=1;i<=m;i++){
		dp[i]|=(dp[i-1]<<1)&tra[b[i]-'a'];
		if(i>=2&&b[i]==b[i-1]) dp[i]|=dp[i-2];
	}
	cout<<(dp[m][n]?"YES\n":"NO\n");
}
int f[maxm],t[Z];
void solve5(){
	f[0]=1;
	for(int i=1;i<=n;i++) t[a[i]-'a']|=(1<<i);
	for(int i=1;i<=m;i++){
		f[i]|=(f[i-1]<<1)&t[b[i]-'a'];
		if(i>=2&&b[i]==b[i-1]) f[i]|=f[i-2];
	}
	cout<<(((f[m]>>n)&1)?"YES\n":"NO\n");
}
void solve6(){
	int tot=0,c=0;
	for(int i=1;i<=m;i++){
		if(b[i]!='a'){
			if(!c){
				c=b[i]-'a';
				continue;
			}
			if(b[i]-'a'!=c) return cout<<"NO\n",void();
			c=0;
		}else{
			if(c) return cout<<"NO\n",void();
			tot++;
		}
	}
	if(c) return cout<<"NO\n",void();
	if(tot>=n&&!((tot-n)&1)) cout<<"YES\n";
	else cout<<"NO\n"; 
}
int g[maxm][7];
void solve7(){
	if((m-n)&1) return cout<<"NO\n",void();
	int k=(m-n)>>1;
	g[0][0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=k;j++){
			if(i>=j+j&&b[i]==a[i-j-j]) g[i][j]|=g[i-1][j];
			if(j&&i>=2&&b[i]==b[i-1]) g[i][j]|=g[i-2][j-1];
		}
	}
	cout<<(g[m][k]?"YES\n":"NO\n");
}
void Init(){}
void Clear(){
	for(int i=0;i<=m;i++){
		dp[i].reset(),f[i]=0;
		for(int j=0;j<7;j++) g[i][j]=0;
	}
	for(int i=0;i<Z;i++) tra[i].reset(),t[i]=0;
}
void Mymain(){
	Clear();
	cin>>a>>b;
	n=a.size(),m=b.size();
	a=' '+a,b=' '+b;
	if(Typ<=4) solve1234();
	if(Typ==5) solve5();
	if(Typ==6) solve6();
	if(Typ==7) solve7();
}
bool Mem2;
signed main(){
	assert(freopen("string.in","r",stdin));
	assert(freopen("string.out","w",stdout));
	cin.tie(0),cout.tie(0);
	Init();int _=read();Typ=read();
	while(_--) Mymain();
	// cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	// cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}