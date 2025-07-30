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
        return scnt;
    }
    graph(int _n):gr(_n),dfn(_n),low(_n),scc(_n),inst(_n),dcnt(0),scnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;graph gr(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        cout<<gr.count()<<'\n';
    }();
    return 0;
}
