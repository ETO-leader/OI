#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,inst,stc,ebcc;
    int dcnt,ebcnt,ecnt;
    auto tarjan(int u,int fid=-1)->void{
        dfn[u]=low[u]=++dcnt;
        inst[u]=true;
        stc.emplace_back(u);
        for(auto&[v,id]:gr[u]) if(id!=fid){
            if(!dfn[v]) tarjan(v,id),low[u]=min(low[u],low[v]);
            else if(inst[v]) low[u]=min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u]){
            ++ebcnt;
            auto ux=-1;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                inst[ux]=false;
                ebcc[ux]=ebcnt;
            }
        }
    }
public:
    auto link(int u,int v){
        ++ecnt;
        gr[u].emplace_back(v,ecnt);
        gr[v].emplace_back(u,ecnt);
    }
    auto ebccof(int u){return ebcc[u];}
    auto count(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
        return ebcnt;
    }
    graph(int _n):gr(_n),dfn(_n),low(_n),ebcc(_n),inst(_n),dcnt(0),ebcnt(-1),ecnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;
    while(cin>>n>>m&&(n||m)){
        graph gr(n);
        vector<pair<int,int>> es;
        set<pair<int,int>> qes;
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            if(qes.count({u,v})) continue;
            qes.emplace(u,v);
            qes.emplace(v,u);
            gr.link(u,v);
            es.emplace_back(u,v);
        }
        cout<<gr.count()<<'\n';
        set<pair<int,int>> ans;
        for(auto&[u,v]:es) if(gr.ebccof(u)!=gr.ebccof(v)){
            ans.emplace(min(u,v)+1,max(u,v)+1);
        }
        for(auto&[u,v]:ans) cout<<u<<' '<<v<<'\n';
    }
    return 0;
}
