#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{
        int v,rev,w;
        edge(auto _v,auto _rev,auto _w):v(_v),rev(_rev),w(_w){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int rst){
        if(u==vx) return rst;
        auto res=0;
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
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,gr[v].size(),w);
        gr[v].emplace_back(u,gr[u].size()-1,0);
    }
    auto flow(int s,int t){
        auto res=0;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int m,n;cin>>m>>n;
    dinic gr(n+7);
    const auto s=n,t=n+1;
    vector<int> c(m);
    for(auto&i:c) cin>>i;
    vector<int> ulas(m,-1);
    cir(i,0,n){
        int k;cin>>k;
        cir(p,0,k){
            int x;cin>>x;--x;
            if(ulas[x]==-1) gr.link(s,i,c[x]);
            else gr.link(ulas[x],i,_inf);
            ulas[x]=i;
        }
        int w;cin>>w;
        gr.link(i,t,w);
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}
