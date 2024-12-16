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
        // clog<<u<<' '<<v<<' '<<w<<'\n';
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
    int n,k;cin>>n>>k;vector<int> imp(n);
    cir(i,0,k){
        int x;cin>>x;--x;imp[x]=true;
    }
    vector<vector<int>> to(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        to[u].emplace_back(v);
        to[v].emplace_back(u);
    }
    vector<int> in(n),out(n);
    nodegen ngen;
    const auto s=ngen(),t=ngen();
    for(auto&i:in) i=ngen();
    for(auto&i:out) i=ngen();
    dinic gr(n*2+7);
    cir(i,0,n) gr.link(in[i],out[i],1);
    cir(i,0,n) if(!imp[i]){
        auto ok=false;
        for(auto&v:to[i]) ok|=imp[v];
        if(ok){
            vector<int> px{i};
            for(auto&v:to[i]) if(!imp[v]) px.push_back(v);
            sort(px.begin(),px.end());
            cir(i,0,(int)(px.size())-1) /*clog<<i<<": "<<px[i]<<' '<<px[i+1]<<'\n',*/gr.link(out[px[i]],in[px[i+1]],_inf);
            gr.link(s,in[px[0]],_inf);
            gr.link(out[px.back()],t,_inf);
        }
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}