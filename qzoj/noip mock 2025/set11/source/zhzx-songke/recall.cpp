#include<bits/stdc++.h>
#define F(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define G(i,l,r) for(int i=(l),i##end=(r);i>=i##end;--i)
#define pii pair<int,int>
#define x first
#define y second
#define mp(x,y) make_pair(x,y)
#define ep emplace_back
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=1e5+9,mod=998244353;
vector<int> E[N];
int dep[N];
int fa[N];
void dfs(int x,int faa)
{
	dep[x]=dep[faa]+1;fa[x]=faa;
	for(auto u:E[x])
		if(u!=faa)dfs(u,x);
}
int sk[N];
bool vis[N];
void dfs1(int x,int faa)
{
	sk[x]=dep[x];
	for(auto u:E[x])
	{
		if(u!=faa)dfs1(u,x);
		if(vis[u])continue;
		sk[x]=max(sk[x],sk[u]);
	}
}
int fac[N],inv[N];
int binom(int x,int y)
{
	return (ll)fac[x+y]*inv[x]%mod*inv[y]%mod;
}
int qpow(int x,int y)
{
	int res=1;
	for(;y;y>>=1,x=(ll)x*x%mod)if(y&1)res=(ll)res*x%mod;
	return res;
}

int dp[109][109][109];
void solve()
{
	memset(vis,0,sizeof vis);
	int n;
	cin>>n;
	F(i,2,n)
	{
		int x,y;
		cin>>x>>y;
		E[x].ep(y);
		E[y].ep(x);
	}
	dfs(1,0);
	vector<int> used;
	int x=max_element(dep+1,dep+n+1)-dep;
	int len=dep[x];
	while(x)used.ep(x),vis[x]=1,x=fa[x];
	reverse(used.begin(),used.end());
	memset(dp,0,sizeof dp);
	F(i,1,len)F(j,0,len)dp[i][i-1][j]=1;
	dfs1(1,0);
	G(i,len,1)F(j,i,len)F(k,0,len)
	{
		dp[i][j][k]=dp[i][j-1][k+1];
//		cerr<<i<<' '<<j<<' '<<k<<' '<<t<<'\n';
		int t=max(i,sk[used[i-1]]-k);
		for(int l=i+1;l<=j;++l)
		{
			if(l>t)dp[i][j][k]=(dp[i][j][k]+(ll)dp[i][l-1][k]*dp[l][j-1][k+1]%mod*binom(l-i,j-l))%mod;
			t=max(sk[used[l-1]]-k,t);
		}
	}
//	cerr<<dp[1][2][0]<<'\n';
	cout<<len<<' '<<dp[1][len][0]<<'\n';
	F(i,1,n)E[i].clear();
}

int main()
{
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	cin.tie(0)->sync_with_stdio(false);
	int testid,T;
	cin>>testid>>T;
	int n=1000;
	fac[0]=1;
	F(i,1,n)fac[i]=(ll)fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	G(i,n,1)inv[i-1]=(ll)inv[i]*i%mod;
	while(T--)solve();

	return 0;
}

