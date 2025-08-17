#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,vis,vbcc;
    vector<pair<int,int>> stc;
    set<pair<int,int>> es;
    int dcnt,ecnt,vbcnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dcnt; 
        for(auto&[v,id]:gr[u]){
            if((!vis[id])&&vbcc[id]<0){
                vis[id]=true;
                stc.emplace_back(v,id);
            }
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(dfn[u]==low[v]){
                    ++vbcnt;
                    es.emplace(u,vbcnt);
                    while(vis[id]){
                        const auto[x,xid]=stc.back();stc.pop_back();
                        vis[xid]=false;
                        es.emplace(x,vbcnt);
                        vbcc[xid]=vbcnt;
                    }
                }
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
public:
    auto link(int u,int v){
        ++ecnt;
        gr[u].emplace_back(v,ecnt);
        gr[v].emplace_back(u,ecnt);
    }
    auto check(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
        return pair(es,vbcnt+1);
    }
    graph(int _n,int _m):gr(_n),dfn(_n),low(_n),vis(_m),vbcc(_m,-1),dcnt(0),ecnt(-1),vbcnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    graph gr(n,m);
    vector<multiset<pair<int,int>>> es(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
        es[u].emplace(v,1);
        es[v].emplace(u,1);
    }
    const auto[ves,cnt]=gr.check();
    vector<vector<int>> tvx(n+cnt);
    for(const auto&[u,v]:ves){
        tvx[u].emplace_back(v+n);
        tvx[v+n].emplace_back(u);
    }
    vector<int> uf(n+cnt);
    auto ftree=[&](auto __self,int u,int f)->void {
        uf[u]=f;
        for(auto&i:tvx[u]) if(i!=f) __self(__self,i,u);
    };
    ftree(ftree,0,-1);
    set<int> uok;
    [&]{
        set<int> pok;
        auto x=n-1;
        while(x) pok.emplace(x),x=uf[x];
        for(const auto&[u,v]:ves) if(pok.contains(v+n)) uok.emplace(u);
    }();
    cir(i,0,n) if(!uok.contains(i)){
        for(auto&[v,w]:es[i]) es[v].extract({i,w});
        es[i].clear();
    }
    cir(i,1,n-1) if(es[i].size()==2){
        const auto[u,wl]=*es[i].begin();
        const auto[v,wr]=*es[i].rbegin();
        es[i].clear();
        es[u].extract({i,wl});
        es[v].extract({i,wr});
        es[u].emplace(v,wl+wr);
        es[v].emplace(u,wl+wr);
    }
    vector<vector<pair<int,int>>> vx(n);
    cir(i,0,n) vx[i]=vector(es[i].begin(),es[i].end());
    vector<int> ans(n-1),vis(n);
    auto fgraph=[&](auto __self,int u,int dis){
        if(u==n-1) return ++ans[dis-1],void();
        vis[u]=true;
        for(auto&[v,w]:vx[u]) if(!vis[v]){
            __self(__self,v,dis+w);
        }
        vis[u]=false;
    };
    fgraph(fgraph,0,0);
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}

