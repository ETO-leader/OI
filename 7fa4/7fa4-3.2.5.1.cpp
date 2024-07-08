#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v,w;};
vector<vector<edge>> G;
vector<lint> D,C,Cx;
lint dfs1(int u,int f=0){
    auto&d=D[u],&cx=Cx[u]=1;
    for(auto&i:G[u]) if(i.v!=f)
        d+=dfs1(i.v,u)+i.w*Cx[i.v],cx+=Cx[i.v];
    return d;
}
void dfs2(int u,lint w=0LL,int f=0){
    auto&c=C[u],&d=D[u];c=d;
    if(u!=1){
        c=C[f]+w*(G.size()-1)-w*2*Cx[u];
    }
    for(auto&i:G[u]) if(i.v!=f) dfs2(i.v,i.w,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);Cx.resize(n+1);
    D.resize(n+1);C.resize(n+1);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    dfs1(1);dfs2(1);
    cout<<accumulate(C.begin(),C.end(),0LL)/2<<'\n';
    return 0;
}