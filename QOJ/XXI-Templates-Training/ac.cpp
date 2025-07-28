#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class scc{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,ins,stc,id;
    int dfncnt,ebcccnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dfncnt;
        stc.emplace_back(u);
        ins[u]=true;
        for(auto&v:gr[u]){
            if(!dfn[v]){
                tarjan(v);
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
        gr[u].emplace_back(v);
    }
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto find(int u){return id[u];}
    scc(int _n):gr(_n),dfn(_n),low(_n),ins(_n),id(_n),dfncnt(0),ebcccnt(-1){}
};
class dag{
private:
    vector<vector<int>> gr;
    vector<int> vis,ord,inc;
    auto dfs(int u)->void{
        vis[u]=true;
        ord.emplace_back(u);
        for(auto&i:gr[u]) if(!(--inc[i])) dfs(i);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        ++inc[v];
    }
    auto check(){
        cir(i,0,(int)(gr.size())) if((!inc[i])&&(!vis[i])) dfs(i);
        return ord;
    }
    dag(int _n):gr(_n),vis(_n),inc(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<pair<int,int>> es(m);
    scc gr(n);
    for(auto&[u,v]:es){
        cin>>u>>v;gr.link(u,v);
    }
    gr.init();
    dag qwq(n);
    for(auto&[u,v]:es) if(gr.find(u)!=gr.find(v)) qwq.link(gr.find(u),gr.find(v));
    const auto ord=qwq.check();
    map<int,vector<int>> ans;
    cir(i,0,n) ans[gr.find(i)].emplace_back(i);
    auto cnt=0;
    for(auto&i:ord) cnt+=!ans[i].empty();
    cout<<cnt<<'\n';
    for(auto&i:ord){
        auto&b=ans[i];
        if(b.empty()) continue;
        cout<<b.size()<<' ';
        for(auto&u:b) cout<<u<<' ';
        cout<<'\n'; 
    }
    return 0;
}
