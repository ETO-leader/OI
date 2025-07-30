#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,inst,stc;
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
            }
        }
    }
public:
    auto link(int u,int v){
        ++ecnt;
        gr[u].emplace_back(v,ecnt);
        gr[v].emplace_back(u,ecnt);
    }
    auto count(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
        return ebcnt;
    }
    graph(int _n):gr(_n),dfn(_n),low(_n),inst(_n),dcnt(0),ebcnt(-1),ecnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;
    while(cin>>n>>m&&(n||m)){
        graph gr(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        cout<<gr.count()<<'\n';
    }
    return 0;
}
