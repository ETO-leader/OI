#include<bits/stdc++.h>
#define maxn 150005
#define fi first
#define se second
#define pii pair<int,int>
#define lowbit(x) ((x)&-(x))
#define conc(x,y,w) son[x][w]=y,fa[y]=x
#define int long long
typedef long long ll;
//inline ll sqr(ll x){return x*x;}
inline ll min(ll x,ll y){return x+=(y<x)*(y-x);}
inline ll max(ll x,ll y){return x+=(x<y)*(y-x);}
inline ll min(ll x,ll y,ll z){return min(min(x,y),z);}
inline ll max(ll x,ll y,ll z){return max(max(x,y),z);}
using namespace std;
mt19937_64 yrand((std::chrono::high_resolution_clock::now()).time_since_epoch().count());
const int N=1145,Mod=998244353,L=2e6+10,inf=(int)1e9+7,Inv=(Mod+1)/2,FM=402653184,Blen=450,G=3,iG=(Mod+1)/G,V=1e9;
inline int reduce(int x){return x-(x>=Mod)*Mod;}
inline int reduce(int x,int Mod){return x-(x>=Mod)*Mod;}

int _C;
int C[114][114];
int n,m,dep[maxn],ed,vis[maxn],fa[maxn],maxx,f[114][114][114],R[maxn];
vector<int>e[maxn];
void dfs1(int x,int lst){
	fa[x]=lst;
	dep[x]=dep[lst]+1;
	if(dep[x]>dep[ed]) ed=x;
	for(int i:e[x]){
		if(i==lst) continue;
		dfs1(i,x);
	}
}
void dfs2(int x,int lst){
	maxx=max(maxx,dep[x]);
	for(int i:e[x]){
		if(i==lst||vis[i]) continue;
		dfs2(i,x);
	}
}
inline void solve(){
	for(int i=1;i<=n;i++) e[i].clear(),vis[i]=0;
	cin>>n;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	ed=0;
	dfs1(1,0);
	cout<<dep[ed]<<' ';
	vector<int>nd;
	while(ed) vis[ed]=1,nd.push_back(ed),ed=fa[ed];
	reverse(nd.begin(),nd.end());
	m=nd.size();
	for(int i=0;i<m;i++){
		maxx=0;
		dfs2(nd[i],0);
		R[i+1]=maxx;
		// cerr<<i+1<<' '<<R[i+1]<<'\n';
	}
	for(int i=1;i<=m;i++) for(int j=0;j<=m;j++) f[i][i][j]=1;
	for(int len=1;len<m;len++){
		for(int i=1;i+len<=m;i++){
			int l=i,r=i+len;
			for(int k=m;k>=0;k--){
				f[l][r][k]=f[l][r-1][min(m,k+1)];
				int maxx=R[l]-k;
				for(int p=l+1;p<=r;p++){
					if(maxx<p){
						if(p!=r) f[l][r][k]=(f[l][r][k]+f[l][p-1][k]*f[p][r-1][min(m,k+1)]%Mod*C[r-l][p-l])%Mod;
						else f[l][r][k]=reduce(f[l][r][k]+f[l][p-1][k]);
					}
					maxx=max(maxx,R[p]-k);
				}
				// cerr<<l<<' '<<r<<' '<<k<<' '<<f[l][r][k]<<'\n';
			}
		}
	}
	cout<<f[1][m][0]<<'\n';
	for(int i=1;i<=m;i++) for(int j=i;j<=m;j++) for(int k=0;k<=m;k++) f[i][j][k]=0;
}
void init(){
	C[0][0]=1;
	for(int i=1;i<=110;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=reduce(C[i-1][j]+C[i-1][j-1]);
		}
	}
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	#endif
	ios::sync_with_stdio(0),cin.tie(0);
	init();
	signed T=1;
	// scanf("%d",&T);
	cin>>_C>>T;
	while(T--) solve();
	cerr<<"Time: "<<clock()*1000/CLOCKS_PER_SEC<<" ms\n";
	return 0;
}
/*
(j-p[i])/i>=k
*/ 
