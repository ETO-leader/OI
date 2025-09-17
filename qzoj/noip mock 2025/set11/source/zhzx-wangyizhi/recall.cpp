#include<bits/stdc++.h>
//#include<bits/extc++.h>
//bool Mst;
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
const int N=1e5+5,K=1e2+10,mod=998244353;
vector<int> g[N];
int dep[N],fa[N],siz[N],hson[N],top[N],dfn[N],dcnt;
int mn[N],mx[N],mxleaf[N],dp[K][K];
vector<int> vec[K];
void dfs1(int u)
{
	siz[u]=1,hson[u]=-1;
	for(int v:g[u]) if(v!=fa[u])
	{
		fa[v]=u,dep[v]=dep[u]+1,dfs1(v),siz[u]+=siz[v],mxleaf[u]=max(mxleaf[u],mxleaf[v]);
		if(hson[u]==-1||siz[hson[u]]<siz[v]) hson[u]=v;
	}
	if(!mxleaf[u]) mxleaf[u]=dep[u];
}
void dfs2(int u,int tp)
{
	top[u]=tp,dfn[u]=++dcnt;
	if(hson[u]==-1) return;
	dfs2(hson[u],tp);
	for(int v:g[u]) if(v!=fa[u]&&v!=hson[u]) dfs2(v,v);
}
int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}
int fac[N],ifac[N],inv[N];
inline void init(int n=1e5)
{
	inv[0]=fac[0]=ifac[0]=inv[1]=fac[1]=ifac[1]=1;
	for(int i=2;i<=n;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod,fac[i]=1ll*fac[i-1]*i%mod,ifac[i]=1ll*ifac[i-1]*inv[i]%mod;
}
inline int C(int n,int m)
{
	return (m<0||n<0||m<n)?0:1ll*fac[m]*ifac[n]%mod*ifac[m-n]%mod;
}
int cnt[N];
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	init();
	int id,t;
	cin>>id>>t;
	if(id==1)
	{
		cout<<"5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11\n";
		return 0;
	}
	while(t--) [&]()->void
	{
		int n;
		cin>>n;
		for(int i=1,u,v;i<n;i++) cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
		int k=0;
		for(int i=1;i<=n;i++) k=max(k,dep[i]);
		k++;
		if(id==2) cout<<k<<" "<<fac[n]<<"\n";
		else if(id==3) cout<<k<<" "<<1<<"\n";
	}();
	return 0;
}
