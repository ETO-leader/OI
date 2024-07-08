#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> UP,G;
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
    int n,q,root;cin>>n>>q>>root;HT=log2(n)+2;
    G.resize(n+1);H.resize(n+1);
    UP.assign(HT+1,vector<int>(n+1));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(root);int zi=0;
    cir(i,0,q){
        int x,y;cin>>x>>y;
        cout<<(zi=lca((x+zi)%n+1,(y+zi)%n+1))<<'\n';
    }
    return 0;
}