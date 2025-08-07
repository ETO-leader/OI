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
        auto cnt=0;
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i),++cnt;
        return make_pair(es,cnt);
    }
    graph(int _n,int _m):gr(_n),dfn(_n),low(_n),vis(_m),vbcc(_m,-1),dcnt(0),ecnt(-1),vbcnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;
    while(cin>>n>>m&&(n||m)){
        graph gr(n,m);
        cir(i,0,m){
            int u,v;cin>>u>>v;
            gr.link(u,v);
        }
        const auto[es,acnt]=gr.check();
        vector<int> cnt(n);
        for(auto&[a,b]:es) ++cnt[a];
        cout<<*max_element(cnt.begin(),cnt.end())+acnt-1<<'\n';
    }
    return 0;
}
