#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    static constexpr auto ups=21;
    vector<vector<int>> up;
    vector<int> dep,uin,uout;
    auto dfs(int u,int&c,int f=0)->void{
        uin[u]=++c;up[0][u]=f;
        cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
        for(auto&[v,w]:gr[u]) if(v!=f) dep[v]=dep[u]+w,dfs(v,c,u);
        uout[u]=c;
    }
    auto is_anciestor(int u,int v){
        return uin[u]-1<uin[v]&&uout[v]-1<uout[u];
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto init(){
        auto c=-1;dfs(0,c);
    }
    auto lca(int u,int v){
        if(is_anciestor(u,v)) return u;
        if(is_anciestor(v,u)) return v;
        for(auto i=ups-1;~i;--i) if(!is_anciestor(up[i][u],v)) u=up[i][u];
        return up[0][u];
    }
    auto dist(int u,int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    tree(int n):gr(n),uin(n),uout(n),up(ups,vector<int>(n)),dep(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;tree gr(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    gr.init();
    cir(i,0,q){
        int u,v;cin>>u>>v;--u;--v;
        cout<<gr.dist(u,v)<<"\n";
    }
    return 0;
}
