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
    int n;
    while(cin>>n&&n){
        int u;graph gr(n,n*n);
        while(cin>>u&&u){
            --u;
            string s;getline(cin,s);
            stringstream info(s);
            int v;
            while(info>>v) gr.link(u,v-1);
        }
        const auto es=gr.check();
        vector<int> cnt(n);
        for(auto&[a,b]:es) ++cnt[a];
        cout<<count_if(cnt.begin(),cnt.end(),[](auto x){return x>1;})<<'\n';
    }
    return 0;
}
