#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
struct edge{int v,id;lint w;};
struct edge_t{int u,v,id;lint w;};
vector<vector<edge>> G;
vector<lint> l,r;
vector<edge_t> es;
namespace graphs_algorithms{
    size_t cntx=0;
    struct HeapNode{
        int u;lint w;
        bool operator<(const HeapNode&hp) const{
            return w>hp.w;
        }
    };
    //dijkstra 求最短路
    vector<lint> dijkstra(int u){
        vector<lint> D(G.size(),_inf),vis(G.size());
        priority_queue<HeapNode> pq;
        pq.push({u,0});D[u]=0;
        while(!pq.empty()){
            auto f=pq.top();pq.pop();
            if(vis[f.u]) continue;
            vis[f.u]=true;
            for(auto&i:G[f.u]){
                if(!vis[i.v]&&D[i.v]>f.w+i.w)
                    D[i.v]=f.w+i.w,pq.push({i.v,f.w+i.w});
            }
        }
        return D;
    }
    //标记 u->v 任意最短路上的边，重命名在最短路上的节点
    vector<bool> road_node_id(int u,int v,vector<lint>&D){
        l[u]=1;vector<bool> ol(es.size());
        while(u!=v){
            for(auto&i:G[u]) if(D[u]==D[i.v]+i.w){
                u=i.v;ol[i.id]=true;break;
            }
            r[u]=++cntx;
            l[u]=r[u]+1;
        }
        return ol;
    }
}
namespace dynamic_programming{
    //求解l,r数组
    template<class comp>
    void run_lr(vector<lint>&D,vector<lint>&lr,vector<bool>&ol){
        vector<lint> nm(D.size());
        iota(nm.begin(),nm.end(),0);
        sort(nm.begin()+1,nm.end(),
            [&D](lint a,lint b){return D[a]<D[b];});
        //初始化顺序
        comp cmp;
        for(auto&i:nm){
            if(!i) continue;
            for(auto&j:G[i]){
                if(ol[j.id]) continue;
                if(D[j.v]==D[i]+j.w&&cmp(lr[i],lr[j.v]))
                    lr[j.v]=lr[i];
            }
        }
    }
    auto run_dp(vector<lint>&D1,vector<lint>&D2,vector<bool>&ol){
        vector<vector<lint>> C1(G.size()),C2(G.size());
        for(auto&[u,v,id,w]:es){
            if(ol[id]) continue;
            if(l[u]<=r[v]){
                auto x=D1[u]+D2[v]+w;
                C1[l[u]].push_back(x);C2[r[v]].push_back(x);
            }
            if(l[v]<=r[u]){
                auto x=D1[v]+D2[u]+w;
                C1[l[v]].push_back(x);C2[r[u]].push_back(x);
            }
        }
        return make_pair(C1,C2);
    }
}
auto run_ans(vector<vector<lint>>&C1,vector<vector<lint>>&C2,lint dx){
    multiset<lint> mts;
    lint ans=dx,cnt=0;
    cir(i,1,graphs_algorithms::cntx+1){
        for(auto&j:C1[i]) mts.insert(j);
        if(!mts.empty()&&*mts.begin()>ans) ans=*mts.begin(),cnt=0;
        if(!mts.empty()&&*mts.begin()==ans) cnt++;
        for(auto&j:C2[i]) mts.erase(mts.find(j));
    }
    return make_pair(ans,cnt);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    l.resize(n+1,_inf);r.resize(n+1);
    es.resize(m);int cnt=0;
    for(auto&[u,v,id,w]:es){
        cin>>u>>v>>w;id=cnt;
        G[u].push_back({v,cnt,w});G[v].push_back({u,cnt,w});
        ++cnt;
    }
    auto D1=graphs_algorithms::dijkstra(1);
    auto D2=graphs_algorithms::dijkstra(n);
    auto ol=graphs_algorithms::road_node_id(1,n,D2);
    dynamic_programming::run_lr<less<lint>>(D1,l,ol);
    dynamic_programming::run_lr<greater<lint>>(D2,r,ol);
    auto [C1,C2]=dynamic_programming::run_dp(D1,D2,ol);
    auto [ans,cntx]=run_ans(C1,C2,D1[n]);
    cout<<ans<<' '<<(ans==D1[n]?m:cntx)<<'\n';
    return 0;
}
