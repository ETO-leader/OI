#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class dinic{
private:
    struct edge{
        int v;lint w;int rev;
        edge(int _v,lint _w,auto r):v(_v),w(_w),rev(r){}
    };
    vector<vector<edge>> gr;
    vector<int> dist,gap,cur;
    bool unusual;
    auto dfs(int u,const int vx,lint rst){
        if(u==vx) return rst;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev]=gr[u][i];
            if(dist[u]==dist[v]+1){
                const auto fl=dfs(v,vx,min(rst,w));
                res+=fl;
                w-=fl;gr[v][rev].w+=fl;
                if(!(rst-=fl)) return res;
            }
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w,(int)(gr[v].size()));
        gr[v].emplace_back(u,0,(int)(gr[u].size())-1);
    }
    auto flow(int s,int t){
        auto res=0ll;
        while(!unusual) res+=dfs(s,t,_infl);
        return res;
    }
    dinic(int _n):gr(_n),dist(_n),gap(_n+7),cur(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n),b(n);
    cir(i,0,n) cin>>a[i]>>b[i];
    const auto v=*ranges::max_element(b)+7;
    auto cnt=-1;
    const auto s=++cnt,t=++cnt;
    vector<int> nd(n);
    for(auto&x:nd) x=++cnt;
    vector id(n,vector<int>(v));
    for(auto&x:id) for(auto&i:x) i=++cnt;
    auto ans=0ll;
    int m;cin>>m;
    vector<pair<int,int>> es(m);
    for(auto&[u,v]:es){
        cin>>u>>v;--u;--v;
        ans+=max(min(b[u],b[v])-a[u],0)+max(min(b[u],b[v])-a[v],0);
        a[u]=max(a[u],min(b[u],b[v]));
        a[v]=max(a[v],min(b[u],b[v]));
        if(b[u]<b[v]) swap(u,v);
    }
    dinic gr(cnt+7);
    cir(i,0,n) cir(w,a[i],v-1) gr.link(id[i][w+1],id[i][w],_infl);
    cir(i,0,n) cir(w,a[i]+1,v) gr.link(id[i][w],t,1);
    vector<int> linked(n);
    for(auto&[u,v]:es){
        if(!linked[u]) gr.link(s,nd[u],max(b[u]-a[u],0));
        linked[u]=true;
        gr.link(nd[u],id[v][b[u]],_infl);
    }
    cout<<gr.flow(s,t)+ans<<'\n';
    return 0;
}
