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
    vector<int64_t> ans;
    const int val;
    auto dfs(int u,int f=-1)->int{
        auto res=0;
        for(auto&i:gr[u]) if(i!=f){
            const auto w=dfs(i,u);
            if(u<val) ans[u]+=(int64_t)(res)*w*2;
            res+=w;
        }
        const auto nres=val-res-(u<val);
        if(u<val) ans[u]+=(int64_t)(res)*nres*2+(res+nres)*2;
        return res+(u<val);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(){return dfs(0),ans;}
    tree(int _n,int _val):gr(_n),ans(_val),val(_val){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    graph gr(n,m);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    const auto es=gr.check();
    tree tr(n*2,n);
    for(auto&[a,b]:es) tr.link(a,b+n);
    const auto ans=tr.check();
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
