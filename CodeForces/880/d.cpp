#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    static constexpr auto ups=21;
    vector<vector<int>> up;
    vector<int> dep,dfn,rdfn;
    auto dfs(int u,int&c,int f=0)->void{
        dfn[u]=++c;up[0][u]=f;
        cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
        for(auto&i:gr[u]) if(i!=f) dep[i]=dep[u]+1,dfs(i,c,u);
        rdfn[u]=c;
    }
    auto is_ancestor(int u,int v){
        return dfn[u]-1<dfn[v]&&rdfn[v]-1<rdfn[u];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(const int r){
        auto c=-1;dfs(r,c);
    }
    auto lca(int u,int v){
        if(is_ancestor(u,v)) return u;
        if(is_ancestor(v,u)) return v;
        for(auto i=ups-1;~i;--i) if(!is_ancestor(up[i][u],v)) u=up[i][u];
        return up[0][u];
    }
    auto depth(int u){
        return dep[u];
    }
    tree(int n):gr(n),dfn(n),rdfn(n),up(ups,vector<int>(n)),dep(n){}
};
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
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto same(int u,int v){return scc[u]==scc[v];}
    graph(int _n):gr(_n),dfn(_n),low(_n),scc(_n),inst(_n),dcnt(0),scnt(-1){}
};
class sccs_graph{
private:
    vector<vector<int>> gr;
    vector<int> vis,ns;
    vector<pair<int,int>> extra;
    tree tr;
    auto dfs(int u)->void{
        vis[u]=true;
        ns.emplace_back(u);
        for(auto&i:gr[u]){
            if(!vis[i]) tr.link(u,i),dfs(i);
            else extra.emplace_back(u,i);
        }
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto calc(const lint k){
        auto res=0ll;
        cir(i,0,(int)(gr.size())) if(!vis[i]){
            ns.clear();
            extra.clear();
            dfs(i);
            tr.init(i);
            auto g=0;
            map<pair<int,int>,int> xcnt;
            for(auto&[u,v]:extra) ++xcnt[{min(u,v),max(u,v)}],g=gcd(g,tr.depth(u)-tr.depth(v)+1);
            for(auto&[a,b]:xcnt) if(b>1) g=gcd(g,2);
            if(!g) continue;
            const auto w=k%g;
            if(!((!w)||(w*2==g))) continue;
            map<int,int> cnt;
            for(auto&x:ns){
                const auto dep=tr.depth(x);
                ++cnt[dep%g];
                const auto nx=(k+dep)%g;
                res+=cnt[nx];
            }
        }
        return res;
    }
    sccs_graph(int _n):gr(_n),vis(_n),tr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,m;lint k;cin>>n>>m>>k;
        graph gr(n);
        vector<pair<int,int>> es(m);
        for(auto&[u,v]:es){
            cin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        gr.init();
        sccs_graph scc(n);
        for(auto&[u,v]:es) if(gr.same(u,v)) scc.link(u,v);
        cout<<scc.calc(k)<<'\n';
    }();
    return 0;
}
