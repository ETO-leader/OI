#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dinic{
private:
    static constexpr lint _inf=1e15+7;
    struct edge{
        int v;lint w;int rev;bool rl;
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,lint cst,const int vx){
        if(u==vx) return cst;
        lint res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev,rl]=gr[u][i];
            if((!w)||(dist[u]-1!=dist[v])) continue;
            const auto fl=dfs(v,min(cst,w),vx);
            res+=fl;w-=fl;gr[v][rev].w+=fl;
            if(!(cst-=fl)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
    auto full(edge e){
        return !e.w;
    }
public:
    auto getedges(){
        set<pair<int,int>> res,resx;
        cir(i,0,(int)(gr.size())){
            for(auto&e:gr[i]) if(!full(e)){
                res.insert({i,e.v});
                if(e.rl) resx.insert({i,e.v});
            }
        }
        return pair(res,resx);
    }
    auto insert(int u,int v,lint w){
        gr[u].push_back({v,w,(int)(gr[v].size()),true});
        gr[v].push_back({u,0,(int)(gr[u].size()-1),false});
    }
    auto flow(int s,int t){
        unusual=false;lint res=0;
        while(!unusual) res+=dfs(s,_inf,t);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),
        gap(_n),dist(_n),unusual(false){}
};
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,scc,stc,ins;
    int dfncnt,scccnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dfncnt;
        stc.push_back(u);ins[u]=true;
        for(auto&i:gr[u]){
            if(!dfn[i]){
                tarjan(i);low[u]=min(low[u],low[i]);
            }else if(ins[i]){
                low[u]=min(low[u],dfn[i]);
            }
        }
        if(low[u]==dfn[u]){
            auto ux=-1;++scccnt;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                ins[ux]=false;scc[ux]=scccnt-1;
            }
        }
    }
public:
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto insert(int u,int v){
        gr[u].push_back(v);
    }
    auto check(int u,int v){
        return scc[u]==scc[v];
    }
    graph(int _n):gr(_n),dfn(_n),low(_n),
        ins(_n),scc(_n),dfncnt(0),scccnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,s,t;cin>>n>>m>>s>>t;
    dinic gr(n+1);
    vector<pair<int,int>> es;
    map<pair<int,int>,lint> cst;
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        cst[{u,v}]+=w;
        es.push_back({u,v});
    }
    for(auto&[a,b]:cst)
        gr.insert(a.first,a.second,b);
    gr.flow(s,t);
    auto[ex,exk]=gr.getedges();
    graph grt(n+1);
    for(auto&[u,v]:ex) grt.insert(u,v);
    grt.init();
    for(auto&[u,v]:es){
        if(exk.count({u,v})){
            cout<<0<<' '<<0<<'\n';continue;
        }
        cout<<(!grt.check(u,v))<<' '<<
            ((!grt.check(u,v))&&grt.check(s,u)&&
            grt.check(v,t))<<'\n';
    }
    return 0;
}
