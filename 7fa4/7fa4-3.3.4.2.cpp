#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
struct HeapNode{
    int v;lint w;
    inline bool operator<(const HeapNode&hp) const{
        return w>hp.w;
    }
};
const lint _inf=1e18+7;
//存边,u->v,val=w
struct edge_t{int u,v;lint w;};
//dijkstra建最短路图
vector<lint> dijkstra(int s){
    priority_queue<HeapNode> pq;
    vector<lint> D(G.size(),_inf),vis(G.size());
    D[s]=0;pq.push({s,0});
    while(!pq.empty()){
        auto [u,w]=pq.top();pq.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(auto&i:G[u]){
            if(!vis[i.v]&&w+i.w<D[i.v])
                D[i.v]=w+i.w,pq.push({i.v,w+i.w});
        }
    }
    return D;
}
vector<vector<edge>> Gr;
set<pair<int,int>> st;
vector<lint> T,D;
//DAG DP
void top_sort(int u){
    for(auto&[v,w]:Gr[u]){
        if(st.count({u,v})) D[v]=max(D[u]+w,D[v]);
        if(!(--T[v])) top_sort(v);
    }
}
vector<edge_t> es;
//找出图上的边
vector<edge_t> runx(int s,int t){
    auto D1=dijkstra(s),D2=dijkstra(t);
    vector<edge_t> res;
    //若对于边 x,有 D1[xᵤ]+D2[xᵥ]+w=D1[t],则加入
    for(auto&[u,v,w]:es){
        if(D1[u]+D2[v]+w==D1[t])
            res.push_back({u,v,w});
        if(D1[v]+D2[u]+w==D1[t])
            res.push_back({v,u,w});
    }
    return res;
}
//往 Gr 塞边
void rebuild(vector<edge_t>&ves){
    for(auto&[u,v,w]:ves)
        Gr[u].push_back({v,w}),++T[v];
}
//往 set (st)  塞边
void ins_in_set(vector<edge_t>&ves){
    for(auto&[u,v,w]:ves)
        st.insert({u,v}),st.insert({v,u});
}
lint run(int n,int s1,int t1,int s2,int t2){
    Gr.clear();T.clear();D.clear();st.clear();
    Gr.resize(n+1);T.resize(n+1);D.resize(n+1);
    auto runs1=runx(s1,t1),runs2=runx(s2,t2);
    rebuild(runs1);ins_in_set(runs2);
    top_sort(s1);
    return *max_element(D.begin(),D.end());
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);es.resize(m);
    Gr.resize(n+1);T.resize(n+1);D.resize(n+1);
    int s1,t1,s2,t2;cin>>s1>>t1>>s2>>t2;
    for(auto&[u,v,w]:es){
        cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    cout<<min(run(n,s1,t1,s2,t2),run(n,s2,t2,s1,t1))<<'\n';
    return 0;
}