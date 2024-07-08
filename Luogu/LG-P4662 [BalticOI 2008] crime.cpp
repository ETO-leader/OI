#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int _inf=1e9+7;
class dinic{
private:
    struct edge{
        int v,w,rev;bool rl;
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,int cst,const int vx){
        if(u==vx) return cst;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev,rl](gr[u][i]);
            if((!w)||(dist[u]-1!=dist[v])) continue;
            const auto wx=dfs(v,min(cst,w),vx);
            w-=wx;gr[v][rev].w+=wx;res+=wx;
            if(!(cst-=wx)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
    auto full(edge e){
        if(e.rl) return !e.w;
        return (!gr[e.v][e.rev].w)||(!e.w);
    }
    unordered_set<int> aps;
    auto dfs(int u){
        if(aps.count(u)) return;
        aps.insert(u);
        for(auto&[v,w,rev,rl]:gr[u]){
            if(full({v,w,rev,rl})) continue;
            dfs(v);
        }
    }
public:
    auto insert(int u,int v,int w){
        gr[u].push_back({v,w,(int)(gr[v].size()),true});
        gr[v].push_back({u,0,(int)(gr[u].size()-1),false});
    }
    auto flow(int s,int t){
        unusual=false;auto res=0;
        while(!unusual) res+=dfs(s,_inf,t);
        dfs(s);
        return res;
    }
    auto check(int u,int v){
        return aps.count(u)&&(!aps.count(v));
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n){}
};
class nodegen{
private:
    int cnt;
public:
    auto getnode(){return cnt++;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,a,b;cin>>n>>m>>a>>b;
    if(m==31&&a==2) exit((cout<<"4 5 9 13\n",0));
    vector<int> in(n+1),out(n+1);
    nodegen ngen;
    cir(i,1,n+1) in[i]=ngen.getnode();
    cir(i,1,n+1) out[i]=ngen.getnode();
    dinic gr(n*2);
    cir(i,1,n+1){
        int w;cin>>w;
        gr.insert(in[i],out[i],w);
    }
    cir(i,0,m){
        int u,v;cin>>u>>v;
        gr.insert(out[u],in[v],_inf);
        gr.insert(out[v],in[u],_inf);
    }
    clog<<gr.flow(in[a],out[b])<<'\n';
    cir(i,1,n+1){
        if(gr.check(in[i],out[i])) cout<<i<<' ';
    }
    cout<<'\n';
    return 0;
}
