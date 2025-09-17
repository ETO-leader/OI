#include<bits/stdc++.h>
#define pb push_back
#define mkp make_pair
using namespace std;
const int maxn=100005,Mod=998244353;
int N,Dep[maxn],ans,fac[maxn],inv[maxn];
vector<int> E[maxn];
int qpow(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=1ll*x*x%Mod) if(y&1) ret=1ll*ret*x%Mod;
	return ret;
}
int Get_C(int x,int y){
	if(x<0||y<0||x<y) return 0;
	return 1ll*fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
int Dn[maxn],Fa[maxn];
void dfs(int x,int fa){
	Dep[x]=Dep[fa]+1;ans=max(ans,Dep[x]);Dn[x]=1;Fa[x]=fa;
	for(int v:E[x]) if(v!=fa) dfs(v,x),Dn[x]=max(Dn[x],Dn[v]+1);
}
int G[maxn],To[maxn],Cnt[maxn],val[maxn];
void reduce(int &x){if(x>=Mod) x-=Mod;}
int F[maxn][105],Sum[105];
int ans2;
void dfs2(int x,int fa){
	for(int v:E[x]) if(v!=fa) dfs2(v,x);
	memset(Sum,0,sizeof Sum);
	for(int i=0;i<Dn[x];i++) F[x][i]=1;
	int p=To[x],pre=x,d=1;
	// printf("! %d ",x);
	// puts("---");
	while(p){
		// printf("%d %d %d\n",p,max(1,val[pre]),Dn[p]-1);
		for(int i=max(1,val[pre]);i<Dn[p];i++){
			int ret=1ll*F[p][i]*G[d]%Mod*Get_C(Dn[p]-i-1+d,d)%Mod;
			reduce(Sum[i-1]+=ret);
		}
		pre=p;p=To[p];d++;
	}
	for(int i=100;i>=0;i--) reduce(Sum[i]+=Sum[i+1]),reduce(F[x][i]+=Sum[i]);
}
int cc[maxn];
void solve(){
	cin>>N;ans=0;ans2=0;
	G[0]=1;
	for(int i=1;i<=N;i++) reduce(G[i]=Get_C(2*i,i)+Mod-Get_C(2*i,i-1));
	for(int i=1;i<=N;i++) E[i].clear(),memset(F[i],0,sizeof F[i]);
	for(int i=1,u,v;i<N;i++) cin>>u>>v,E[u].pb(v),E[v].pb(u);
	dfs(1,0);
	for(int i=1;i<=N;i++){
		To[i]=0;Cnt[i]=0;
		for(int j:E[i]) if(j!=Fa[i]){
			if(!To[i]) To[i]=j,Cnt[i]=1;else
			if(Dn[j]>Dn[To[i]]) To[i]=j,Cnt[i]=1;
			else if(Dn[j]==Dn[To[i]]) Cnt[i]++;
		}
		if(Cnt[i]>1) To[i]=0;
		else for(int j:E[i]) if(j!=Fa[i]&&Dn[j]!=Dn[To[i]]) val[i]=max(val[i],Dn[j]);
	}
	// for(int i=1;i<=N;i++) printf("%d%c",To[i],i==N?'\n':' ');
	printf("%d ",ans);
	dfs2(1,0);
	int x=1;
	while(x){
		ans2=(ans2+1ll*F[x][0]*G[Dep[x]-1]%Mod*Get_C(ans-1,Dep[x]-1))%Mod;
		// printf("!! %d %d\n",x,1ll*F[x][0]*G[Dep[x]-1]%Mod*Get_C(ans-1,Dep[x]-1)%Mod);
		if(val[x]) break;
		x=To[x];
	}
	// for(int i=1;i<=N;i++){
	// 	printf("i = %d:\n",i);
	// 	for(int j=0;j<=Dn[i];j++) printf("%d ",F[i][j]);
	// 	puts("");
	// }
	printf("%d\n",ans2);
}
int main(){
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	fac[0]=1;
	for(int i=1;i<maxn;i++) fac[i]=1ull*fac[i-1]*i%Mod;
	inv[maxn-1]=qpow(fac[maxn-1],Mod-2);
	for(int i=maxn-1;i;i--) inv[i-1]=1ull*inv[i]*i%Mod;
	cin.tie(0)->sync_with_stdio(0);
	int c,T;cin>>c>>T;
	while(T--) solve();
	return 0;
}