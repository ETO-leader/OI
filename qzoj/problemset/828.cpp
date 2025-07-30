#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,scc,inst,stc;
    int dcnt,scnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dcnt;
        inst[u]=true;
        stc.emplace_back(u);
        for(auto&i:gr[u]){
            if(!dfn[i]) tarjan(i),low[u]=min(low[u],low[i]);
            else if(inst[i]) low[u]=min(low[u],dfn[i]);
        }
        if(dfn[u]==low[u]){
            ++scnt;
            auto ux=-1;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                inst[ux]=false;
                scc[ux]=scnt;
            }
        }
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto count(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
        vector<vector<int>> res(scnt+1);
        cir(i,0,(int)(gr.size())) res[scc[i]].emplace_back(i);
        return res;
    }
    graph(int _n):gr(_n),dfn(_n),low(_n),scc(_n),inst(_n),dcnt(0),scnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    const auto info=gr.count();
    cout<<info.size()<<'\n';
    for(auto&x:info){
        cout<<x.size()<<' ';
        for(auto&i:x) cout<<i+1<<' ';
        cout<<'\n';
    }
    return 0;
}
