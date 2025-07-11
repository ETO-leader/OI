#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class ebcc{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,ins,stc,id;
    int dfncnt,ebcccnt,ecnt;
    auto tarjan(int u,int f=-1)->void{
        dfn[u]=low[u]=++dfncnt;
        stc.emplace_back(u);
        ins[u]=true;
        for(auto&[v,eid]:gr[u]) if(eid!=f){
            if(!dfn[v]){
                tarjan(v,eid);
                low[u]=min(low[u],low[v]);
            }else if(ins[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(dfn[u]==low[u]){
            ++ebcccnt;
            auto v=-1;
            while(v!=u){
                v=stc.back();stc.pop_back();
                ins[v]=false;
                id[v]=ebcccnt;
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
    auto find(int u){return id[u];}
    ebcc(int _n):gr(_n),dfn(_n),low(_n),ins(_n),id(_n),dfncnt(0),ebcccnt(0),ecnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<pair<int,int>> es(m);
    ebcc gr(n);
    for(auto&[u,v]:es){
        cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    gr.init();
    for(auto&[u,v]:es){
        if(gr.find(u)!=gr.find(v)) cout<<u+1<<' '<<v+1<<'\n';
    }
    return 0;
}
