#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class ssp{
private:
    struct edge{
        int v;lint fl,w;int rev;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<int> fr,eid;
    vector<lint> h;
    auto dijkstra(int s,int t){
        const auto n=(int)(gr.size());
        vector<lint> dis(n,_infl),rest(n),vis(n);
        priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<>> q;
        q.emplace(0,s);
        rest[s]=_infl;dis[s]=0;
        while(!q.empty()){
            const auto[uw,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            auto cnt=-1;
            for(auto&[v,fl,w,rev]:gr[u]) if(++cnt;dis[v]>dis[u]+w+h[u]-h[v]&&fl){
                dis[v]=dis[u]+w+h[u]-h[v];
                rest[v]=min(rest[u],fl);
                fr[v]=u;eid[v]=cnt;
                q.emplace(dis[v],v);
            }
        }
        cir(i,0,n) h[i]=min(h[i]+dis[i],_infl);
        return rest[t];
    }
    auto update(int s,int t,lint&flw,lint&cur){
        const auto fl=dijkstra(s,t);
        if(!fl) return false;
        flw+=fl;
        for(;t!=s;t=fr[t]){
            const auto u=fr[t];
            gr[u][eid[t]].fl-=fl;
            gr[t][gr[u][eid[t]].rev].fl+=fl;
            cur+=gr[u][eid[t]].w*fl;
        }
        return true;
    }
public:
    auto link(int u,int v,lint fl,lint w){
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto fl=0ll,ans=0ll;
        while(update(s,t,fl,ans));
        return make_pair(fl,ans);
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n),h(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    ssp gr(n+1);
    cir(i,0,m){
        int u,v,fl,w;cin>>u>>v>>fl>>w;
        gr.link(u,v,fl,w);
    }
    const auto[fl,cst]=gr.flow(1,n);
    cout<<fl<<' '<<cst<<'\n';
    return 0;
}
