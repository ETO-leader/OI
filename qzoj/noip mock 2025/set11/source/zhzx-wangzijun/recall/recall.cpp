
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
const ll mod = 998244353;
inline ll read(){
	ll x; scanf("%lld",&x); return x;
}
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
int n,md[100005],dep[100005]; vector<int>E[100005],w[100005];
int cnt[105],dp[105][105][105];
void dfs(int x,int fa){
	md[x]=1; dep[x]=dep[fa]+1;
	for(auto y: E[x]){
		if(y==fa) continue;
		dfs(y,x);
		md[x]=max(md[x], 1+md[y]);
	}
	// cout<<x<<" md = "<<md[x]<<endl;
}
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
int pig[105][105];
void procedure(){
	memset(pig,0,sizeof(pig));
	memset(dp,0,sizeof(dp));
	memset(cnt,0,sizeof(cnt));
	n=read();
	for(int i=1;i<=n;i++) E[i].clear(),w[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v); E[v].pb(u);
	}
	dfs(1,0); int N=md[1];

	for(int c=0;c<N;c++)
		for(int i=1;i<=n;i++) pig[c][dep[i]] += (md[i] > c);
	for(int l=0;l<=N+1;l++) for(int r=0;r<=N+1;r++)
		dp[N][l][r] = 1;
	for(int c=N-1;c>=0;c--){
		for(int l=0;l<=N+1;l++) for(int r=0;r<=N+1;r++)
			if(l>r) dp[c][l][r] = 1;
		for(int l=N;l>=1;l--)
			for(int r=l;r<=N;r++){
				// memset(cnt,0,sizeof(cnt));

				// for(int d=l;d<=r;d++){
				// 	for(auto x: w[d]) if(md[x] > c) cnt[d]++;
				// }
				// dp[c][l][r] = dp[c+1][l][r-1];
				for(int d=l;d<=r;d++){
					if(pig[c][d]==1){
						dp[c][l][r]=(dp[c][l][r]+1ull*dp[c][l][d-1]*dp[c+1][d][r-1]%mod*binom(r-l,d-l))%mod;
						// cout<<"contri "<<dp[c][l][d-1]<<" * "<<dp[c+1][d][l-1]<<endl;
					}
				}
				// if(dp[c][l][r]) cout<<c<<","<<l<<","<<r<<" dp = "<<dp[c][l][r]<<endl;
			}
	}
	printf("%d %d\n", md[1], dp[0][1][N]);
}
int main(){
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	int id=read(), T=read();
	math_init();
	while(T--) procedure();
}