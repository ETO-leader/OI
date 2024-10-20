#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class ebcgraph{
private:
    struct edge{
        int v,id;
        edge(int _v,int _id):v(_v),id(_id){}
    };
    vector<vector<edge>> gr;
    vector<int> dfn,low,ebcc,stc,inst;
    int dcnt,ebcnt,ecnt;
    auto tarjan(int u,int fid=-1)->void{
        dfn[u]=low[u]=++dcnt;
        inst[u]=true;stc.push_back(u);
        for(auto&[v,id]:gr[u]) if(id!=fid){
            if(!dfn[v]) tarjan(v,id),low[u]=min(low[u],low[v]);
            else if(inst[v]) low[u]=min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u]){
            auto ux=-1;++ebcnt;
            while(u!=ux){
                ux=stc.back();stc.pop_back();
                ebcc[ux]=ebcnt;inst[ux]=false;
            }
        }
    }
public:
    auto link(int u,int v){
        ++ecnt;
        gr[u].emplace_back(v,ecnt);
        gr[v].emplace_back(u,ecnt);
    }
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto gebcc(const int u){return ebcc[u];}
    ebcgraph(auto _n):gr(_n),dfn(_n),low(_n),
        ebcc(_n),inst(_n),dcnt(0),ebcnt(-1),ecnt(-1){}
};
class dijgraph{
private:
    vector<vector<pair<int,lint>>> gr;
    auto dijkstra(const auto ux,const auto vx){
        priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<pair<lint,int>>> q;
        q.emplace(0,ux);
        const auto n=(int)(gr.size());
        vector dis(n,_infl);dis[ux]=0;
        vector<bool> vis(n);
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wx]:gr[u]) if(dis[v]>w+wx){
                q.emplace((dis[v]=w+wx),v);
            }
        }
        set qx{vx};
        unordered_set<int> aps;
        ebcgraph res(gr.size());
        set<tuple<int,int,lint>> ces;
        while(!qx.empty()){
            const auto u=*qx.begin();qx.erase(qx.begin());
            for(auto&[v,w]:gr[u]) if(dis[u]==dis[v]+w){
                ces.emplace(min(u,v),max(u,v),w);
                res.link(u,v);
                if(!aps.contains(v)) qx.insert(v),aps.insert(v);
            }
        }
        return pair(res,ces);
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto check(int u,int v){
        return dijkstra(u,v);
    }
    dijgraph(auto _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;dijgraph gr(n);
    vector<tuple<int,int,lint>> es(m);
    map<tuple<int,int,lint>,int> cnt;
    for(auto&[u,v,w]:es){
        cin>>u>>v>>w;--u;--v;
        tie(u,v)=minmax(u,v);
        ++cnt[{u,v,w}];
        gr.link(u,v,w);
    }
    auto[ngr,nes]=gr.check(0,n-1);
    ngr.init();
    for(auto&[u,v,w]:es) [&](){
        if(cnt[{u,v,w}]>1) return cout<<"No\n",void();
        if(!nes.contains({u,v,w})) return cout<<"No\n",void();
        if(ngr.gebcc(u)==ngr.gebcc(v)) return cout<<"No\n",void();
        cout<<"Yes\n";
    }();
    return 0;
}
