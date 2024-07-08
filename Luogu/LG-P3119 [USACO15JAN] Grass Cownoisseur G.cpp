#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
vector<VI> G,DAG,rDAG;
struct edge_t{int u,v;};
vector<edge_t> es;
VI dfn,low,scc,siz,ins,st;
void tarjan(int u,int&dfncnt){
    dfn[u]=low[u]=++dfncnt;
    st.push_back(u);ins[u]=true;
    for(auto&i:G[u]){
        if(!dfn[i]){
            tarjan(i,dfncnt);
            low[u]=min(low[u],low[i]);
        }else if(ins[i]){
            low[u]=min(low[u],dfn[i]);
        }
    }
    if(low[u]==dfn[u]){
        int x=-1;
        const auto scccnt=siz.size();
        siz.push_back(0);
        while(x!=u){
            x=st.back();st.pop_back();
            scc[x]=scccnt;++siz[scccnt];
            ins[x]=false;
        }
    }
}
void build_g(){
    set<pair<int,int>> aps;
    DAG.resize(siz.size());
    rDAG.resize(siz.size());
    for(auto[u,v]:es){
        u=scc[u];v=scc[v];
        if(u==v) continue;
        if(aps.count({u,v})||aps.count({v,u}))
            continue;
        aps.insert({u,v});
        DAG[u].push_back(v);
        rDAG[v].push_back(u);
    }
}
void dfs(vector<VI>&dag,int u,VI&vis){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:dag[u]) dfs(dag,i,vis);
}
auto getsz(vector<VI>&dag){
    const int nx=siz.size()-1;
    VI res(nx+1,-_inf),fin(nx+1),vis(nx+1);
    dfs(dag,scc[1],vis);
    cir(i,1,nx+1) if(vis[i]){
        for(auto&x:dag[i]) if(vis[x])
            ++fin[x];
    }
    queue<int> q;q.push(scc[1]);
    res[scc[1]]=siz[scc[1]];
    while(!q.empty()){
        auto u=q.front();q.pop();
        for(auto&i:dag[u]) if(vis[i]){
            res[i]=max(res[i],res[u]+siz[i]);
            if(!(--fin[i])) q.push(i);
        }
    }
    return res;
}
void init(int n,int m){
    G.resize(n+1);dfn.resize(n+1);
    scc.resize(n+1);low.resize(n+1);
    ins.resize(n+1);es.resize(m);
    siz.resize(1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;init(n,m);
    for(auto&[u,v]:es){
        cin>>u>>v;G[u].push_back(v);
    }
    [&](){
        int dc=0;
        cir(i,1,n+1) if(!dfn[i]) tarjan(i,dc);
    }();
    build_g();
    auto D=getsz(DAG),rD=getsz(rDAG);
    int ans=0;
    for(auto&[u,v]:es){
        ans=max(ans,D[scc[v]]+
            rD[scc[u]]-siz[scc[1]]);
    }
    cout<<ans<<'\n';
    return 0;
}
