#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{
        int v,w,rev;
        edge(auto _v,auto _w,auto _rev):v(_v),w(_w),rev(_rev){}
    };
    vector<vector<edge>> gr;
    vector<int> dist,cur,gap;
    bool unusual;
    auto dfs(int u,const int vx,int fl){
        if(u==vx) return fl;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev]=gr[u][i];
            if((!w)||(dist[u]!=dist[v]+1)) continue;
            const auto fx=dfs(v,vx,min(fl,w));
            w-=fx;gr[v][rev].w+=fx;
            res+=fx;
            if(!(fl-=fx)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w,(int)(gr[v].size()));
        gr[v].emplace_back(u,0,(int)(gr[u].size())-1);
    }
    auto flow(const int s,const int t){
        auto res=0;unusual=false;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),gap(_n+7),dist(_n){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return ++cnt;}
    nodegen():cnt(-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,c;cin>>n>>m>>c;
    vector<int> p(c);
    for(auto&i:p) cin>>i,--i;
    dinic gr(n+c*2+7);
    nodegen ngen;
    vector<int> nid(n),in(c),out(c);
    for(auto&i:nid) i=ngen();
    for(auto&i:in) i=ngen();
    for(auto&i:out) i=ngen();
    cir(i,0,c) gr.link(in[i],out[i],1),gr.link(out[i],nid[p[i]],_inf),gr.link(nid[p[i]],in[i],_inf);
    cir(i,0,m){
        int u,v,r;cin>>u>>v>>r;--u;--v;--r;
        if(u==p[r]) gr.link(out[r],nid[v],_inf);
        else gr.link(nid[u],in[r],_inf);
    }
    cout<<gr.flow(nid[0],nid[n-1])<<'\n';
    return 0;
}
