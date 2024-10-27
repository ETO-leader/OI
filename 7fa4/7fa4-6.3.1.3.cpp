#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,vbcc,vis;
    vector<pair<int,int>> stc;
    int dcnt,vcnt,ide;
    set<pair<int,int>> es;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dcnt;
        for(auto&[v,id]:gr[u]){
            if((vbcc[id]<0)&&(!vis[id])){
                vis[id]=true;
                stc.emplace_back(id,v);
            }
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(dfn[u]==low[v]){
                    ++vcnt;
                    es.emplace(u,vcnt);
                    while(vis[id]){
                        const auto[idi,vi]=stc.back();
                        stc.pop_back();
                        vbcc[idi]=vcnt;
                        es.emplace(vi,vcnt);
                        vis[idi]=false;
                    }
                }
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
public:
    auto insert(int u,int v){
        ++ide;
        gr[u].emplace_back(v,ide);
        gr[v].emplace_back(u,ide);
    }
    auto check(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
        return es;
    }
    auto gvbcc(int eid){return vbcc[eid];}
    graph(int _n,int _m):gr(_n),dfn(_n),low(_n),vbcc(_m,-1),vis(_m),dcnt(0),vcnt(-1),ide(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n,m);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.insert(u,v);
    }
    const auto ex=gr.check();
    map<int,vector<int>> ei;
    cir(i,0,m) ei[gr.gvbcc(i)].push_back(i);
    cout<<ei.size()<<'\n';
    for(auto[a,b]:ei){
        cout<<b.size()<<' ';
        for(auto&i:b) ++i;
        copy(b.begin(),b.end(),ostream_iterator<int>(cout," "));
        cout<<'\n';
    }
    cout<<ex.size()<<'\n';
    for(auto&[a,b]:ex) cout<<a+1<<' '<<b+1<<'\n';
    return 0;
}
