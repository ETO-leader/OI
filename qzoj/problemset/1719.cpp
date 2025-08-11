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
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    for(int m,ucase=1;cin>>m&&m;++ucase){
        auto n=0;
        vector<pair<int,int>> x(m);
        for(auto&[u,v]:x) cin>>u>>v,--u,--v,n=max({n,u+1,v+1});
        graph gr(n,m);
        for(auto&[u,v]:x) gr.link(u,v);
        const auto es=gr.check();
        vector<int> cnt(n);
        for(auto&[a,b]:es) ++cnt[a];
        vector<int> vcnt(n),siz(n);
        for(auto&[a,b]:es) vcnt[b]+=(cnt[a]>1),siz[b]+=(cnt[a]==1);
        auto ucnt=0;
        auto ans=1ull;
        static const auto contrib=array<int,3>{2,1,0};
        cir(i,0,n) if(siz[i]){
            ucnt+=contrib[min(vcnt[i],2)];
            if((!vcnt[i])&&siz[i]>1) ans*=(uint64_t)(siz[i])*(siz[i]-1)/2;
            if(vcnt[i]==1) ans*=siz[i];
        }
        cout<<"Case "<<ucase<<": "<<ucnt<<' '<<ans<<'\n';
    }
    return 0;
}
