#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=numeric_limits<int>::max();
class dinic{
private:
    struct edge{
        int v,rev,w,fv;
        edge(auto _v,auto _rev,auto _w,auto _f):v(_v),rev(_rev),w(_w),fv(_f){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int rst){
        if(u==vx) return rst;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl,fv]=gr[u][i];
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
        gr[u].emplace_back(v,gr[v].size(),w,w);
        gr[v].emplace_back(u,gr[u].size()-1,0,0);
    }
    auto flow(int s,int t){
        auto res=0ll;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    auto info(){
        vector<tuple<int,int,int>> es;
        cir(u,0,(int)(gr.size())) for(auto&[v,rev,fl,fv]:gr[u]) if(fv>fl){
            es.emplace_back(u,v,fv-fl);
        }
        return es;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n+7),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;dinic gr(n);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    const auto ans=gr.flow(0,n-1);
    cout<<ans<<'\n';
    const auto info=gr.info();
    vector<deque<pair<int,int>>> vx(n);
    for(auto&[u,v,w]:info) vx[u].emplace_back(v,w);
    auto sum=0;
    while(sum<ans){
        auto u=0,w=_inf;
        vector<int> ux{0};
        while(u!=n-1){
            w=min(w,vx[u].front().second);
            u=vx[u].front().first;
            ux.emplace_back(u);
        }
        sum+=w;
        cir(i,0,(int)(ux.size())-1){
            vx[ux[i]].front().second-=w;
            if(!vx[ux[i]].front().second) vx[ux[i]].pop_front();
        }
        cout<<ux.size()<<' '<<w<<' ';
        for(auto&i:ux) cout<<i+1<<' ';
        cout<<'\n';
    }
    return 0;
}
