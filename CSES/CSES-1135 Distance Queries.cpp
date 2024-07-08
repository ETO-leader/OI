#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> UP,G;
vector<int> H;int HT;
void dfs(int u,int f=0){
    UP[u][0]=f;H[u]=H[f]+1;
    cir(i,1,HT+1) UP[u][i]=UP[UP[u][i-1]][i-1];
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
int lca(int u,int v){
    int cnt=0;
    if(u==v) return cnt;
    if(H[u]<H[v]) swap(u,v);
    cir(i,0,HT) if((1<<i)&(H[u]-H[v]))
        u=UP[u][i],cnt+=(1<<i);
    if(u==v) return cnt;
    for(int i=HT;~i;--i) if(UP[u][i]!=UP[v][i])
        u=UP[u][i],v=UP[v][i],cnt+=(1<<(i+1));
    return cnt+2;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;HT=log2(n)+2;
    G.resize(n+1);H.resize(n+1);
    UP.assign(n+1,vector<int>(HT+1));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        cout<<lca(u,v)<<'\n';
    }
    return 0;
}