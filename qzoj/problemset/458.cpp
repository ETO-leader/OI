#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class dinic{
private:
    struct edge{
        int v,rev;lint w;
        edge(auto _v,auto _rev,auto _w):v(_v),rev(_rev),w(_w){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,lint rst){
        if(u==vx) return rst;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl]=gr[u][i];
            if(dist[u]!=dist[v]+1||(!fl)) continue;
            const auto vw=dfs(v,vx,min(rst,fl));
            fl-=vw;gr[v][rev].w+=vw;res+=vw;
            if(!(rst-=vw)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,gr[v].size(),w);
        gr[v].emplace_back(u,gr[u].size()-1,0);
    }
    auto flow(int s,int t){
        auto res=0ll;
        while(!unusual) res+=dfs(s,t,_infl);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;dinic gr(n);
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    cout<<gr.flow(0,n-1)<<'\n';
    return 0;
}
