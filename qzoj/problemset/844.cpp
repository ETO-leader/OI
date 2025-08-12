#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=numeric_limits<int>::max();
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
    int n,x;cin>>n>>x;
    dinic gr(n*2+7);
    const auto s=n*2,t=n*2+1;
    gr.link(s,n,x);
    cir(i,1,n){
        int x,y;cin>>x>>y;
        gr.link(i,i+n,x);
        gr.link(i+n,t,y);
    }
    int m;cin>>m;
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u+n,v,_inf);
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}
