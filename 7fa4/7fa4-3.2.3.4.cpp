#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> UP;
vector<vector<int>> G;
vector<int> H;int HT;
void dfs(int u,int f=0){
    UP[0][u]=f;H[u]=H[f]+1;
    cir(i,1,HT+1) UP[i][u]=UP[i-1][UP[i-1][u]];
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
int lca(int u,int v){
    if(u==v) return u;
    if(H[u]<H[v]) swap(u,v);
    cir(i,0,HT) if((1<<i)&(H[u]-H[v])) u=UP[i][u];
    if(u==v) return u;
    for(int i=HT;~i;--i) if(UP[i][u]!=UP[i][v])
        u=UP[i][u],v=UP[i][v];
    return UP[0][u];
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,q;cin>>n>>q;HT=log2(n)+2;
    G.resize(n+1);H.resize(n+1);
    UP.assign(HT+1,vector<int>(n+1));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1);
    cir(i,0,q){
        int x,y,z;cin>>x>>y>>z;
        int s=lca(x,y),d=lca(y,z),g=lca(z,x),rl;
		if(s==d) rl=g;
		else if(s==g) rl=d;
		else rl=s;
		int ans=H[x]+H[y]+H[z]-H[s]-H[d]-H[g];
		cout<<rl<<' '<<ans<<'\n';
    }
	return 0;
}