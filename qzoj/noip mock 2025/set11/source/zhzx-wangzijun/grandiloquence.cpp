#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); };
int n,m,k,fa[400005],dep[400005],dfn[400005],sz[400005],tim,v[400005];
int sub;
vector<int>E[400005];
void dfs(int x){
	dfn[x]=(++tim); sz[x]=1;
	for(auto y: E[x]){
		dep[y]=dep[x]+1;
		dfs(y); sz[x]+=sz[y];
	}
}
void down(int x,int c){
	v[x]=c;
	for(auto y: E[x])
		down(y,(c+1)%k);
}
int gett(int x,int c){
	int now=(v[x]==c);
	for(auto y: E[x]) now+=gett(y,c);
	return now;
}
void solve1(){
	int lst=0,cur=n;
	while(m--){
		int op=read();
		if(op==1){
			int u=read(), c=read();
			if(!(sub&1)) u^=lst,c^=lst;
			c--;
			down(u,c);
		}else if(op==2){
			int u=read(), c=read();
			if(!(sub&1)) u^=lst,c^=lst;
			c--;
			printf("%d\n", lst=gett(u,c));
		}else{
			E[read()^lst].pb(++cur);
			v[cur]=-1;
		}
	}
}
void procedure(){
	sub=read();	
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) fa[i]=read(),E[fa[i]].pb(i),v[i]=-1;
	if(sub<=2){
		solve1();
	}
}
int main(){
	freopen("grandiloquence.in","r",stdin);
	freopen("grandiloquence.out","w",stdout);
	procedure();
	return 0;
}