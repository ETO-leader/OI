#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int _inf=1e9+7;
class dinic{
private:
    struct edge{int v,rev;lint w;};
    vector<vector<edge>> G;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,lint rst,int t){
        if(u==t) return rst;
        lint res=0;
        for(auto&i=cur[u];i<(int)(G[u].size());++i){
            auto&e=G[u][i];
            if(e.w&&dist[u]-1==dist[e.v]){
                auto rx=dfs(e.v,min(rst,e.w),t);
                e.w-=rx;
                G[e.v][e.rev].w+=rx;
                res+=rx;
                if(!(rst-=rx)) return res;
            }
        }
        if(!--gap[dist[u]]) unusual=true;
        gap[++dist[u]]++;
        cur[u]=0;
        return res;
    }
public:
    auto insert(int u,int v,lint w){
        G[u].push_back({v,(int)(G[v].size()),w});
        G[v].push_back({u,(int)(G[u].size())-1,0});
    }
    auto get(int s,int t){
        lint res=0;unusual=false;
        while(!unusual) res+=dfs(s,_inf,t);
        return res;
    }
    dinic(int n):G(n),cur(n),dist(n),gap(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,s,t;cin>>n>>m>>s>>t;
    dinic gr(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        gr.insert(u,v,w);
    }
    cout<<gr.get(s,t)<<'\n';
    return 0;
}
