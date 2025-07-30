#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
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
        return scc;
    }
    graph(int _n):gr(_n),dfn(_n),low(_n),scc(_n),inst(_n),dcnt(0),scnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;graph gr(n);
    int p;cin>>p;
    vector<pair<int,int>> info(p);
    for(auto&[a,b]:info) cin>>a>>b,--a;
    int r;cin>>r;
    vector<pair<int,int>> es;
    cir(i,0,r){
        int u,v;cin>>u>>v;--u;--v;
        es.emplace_back(u,v);
        gr.link(u,v);
    }
    const auto sccid=gr.count();
    const auto ex=*max_element(sccid.begin(),sccid.end())+1;
    vector<int> w(ex,_inf),inc(ex);
    for(auto&[a,b]:info) w[sccid[a]]=min(w[sccid[a]],b);
    for(auto&[u,v]:es) if(sccid[u]!=sccid[v]) ++inc[sccid[v]];
    auto ans=0ll;
    cir(u,0,ex) if((!inc[u])&&(w[u]==_inf)){
        cout<<"NO"<<'\n';
        cout<<find(sccid.begin(),sccid.end(),u)-sccid.begin()+1<<'\n';
        exit(0);
    }else if(!inc[u]) ans+=w[u];
    cout<<"YES"<<'\n';
    cout<<ans<<'\n';
    return 0;
}
