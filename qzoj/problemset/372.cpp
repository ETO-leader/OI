#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,vbcc,vis,stc;
    int dfncnt,vcnt,ecnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dfncnt;
        for(auto&[v,id]:gr[u]){
            if(vbcc[id]<0&&(!vis[id])){
                vis[id]=true;
                stc.emplace_back(id);
            }
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(dfn[u]==low[v]){
                    ++vcnt;
                    while(vis[id]){
                        const auto vid=stc.back();
                        stc.pop_back();
                        vis[vid]=false;
                        vbcc[vid]=vcnt;
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
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto check(int u) const{
        set<int> test;
        for(auto&[v,id]:gr[u]) test.emplace(vbcc[id]);
        return test.size()>1;
    }
    graph(int _n,int _m):gr(_n),dfn(_n),low(_n),vbcc(_m,-1),vis(_m),dfncnt(0),vcnt(-1),ecnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n,m);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        if(u!=v) gr.link(u,v);
    }
    gr.init();
    vector<int> ans;
    cir(i,0,n) if(gr.check(i)) ans.emplace_back(i);
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i+1<<' ';
    cout<<'\n';
    return 0;
}
