#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
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
        return es;
    }
    graph(int _n,int _m):gr(_n),dfn(_n),low(_n),vis(_m),vbcc(_m,-1),dcnt(0),ecnt(-1),vbcnt(-1){}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> fr;
    auto dfs(int u,int f=-1)->void{
        fr[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,u);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto path(int u,int v){
        dfs(u);
        set<int> res;
        while(v!=u&&v>-1){
            res.emplace(v=fr[v]);
        }
        if(v!=-1) res.erase(u);
        return res;
    }
    tree(int _n):gr(_n),fr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;
    while(cin>>n&&n){
        graph gr(n,n*n);
        int u,v;
        while(cin>>u>>v&&u&&v) gr.link(u-1,v-1);
        const auto info=gr.check();
        tree tr(n*2);
        for(auto&[a,b]:info) tr.link(a,b+n);
        cin>>u>>v;--u;--v;
        const auto ans=*tr.path(u,v).begin();
        if(ans<0||ans>n-1) cout<<"No solution\n";
        else cout<<ans+1<<'\n';
    }
    return 0;
}
