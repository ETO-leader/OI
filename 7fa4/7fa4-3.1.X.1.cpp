#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
namespace error_level{
    void impossible(){
        cout<<"Forever love\n";exit(0);
    }
}
const lint _inf=1e18+7;
namespace shortest_path{
    struct HeapNode{
        int u;lint w;
        bool operator<(const HeapNode&hp) const{
            return w>hp.w;
        }
    };
    lint dijkstra(int n,int s,int t){
        vector<lint> D(n+1,_inf),vis(n+1);
        priority_queue<HeapNode> pq;
        D[s]=0;pq.push({s,0});
        while(!pq.empty()){
            auto [u,w]=pq.top();pq.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wi]:G[u]){
                if(!vis[v]&&D[v]>w+wi)
                    D[v]=w+wi,pq.push({v,w+wi});
            }
        }
        return D[t];
    }
    lint spfa(int n,int s,int t){
        vector<lint> D(n+1,_inf),inx(n+1);
        queue<int> q;q.push(s);
        D[s]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            if((++inx[u])>n) error_level::impossible();
            for(auto&[v,w]:G[u])
                if(D[u]+w<D[v]) D[v]=D[u]+w,q.push(v);
        }
        return D[t];
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;lint d;cin>>n>>m>>d;
    G.resize(n+1);
    bool type2_tag=false;
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        type2_tag|=(w>0);
        G[u].push_back({v,-w});
    }
    cout<<d+(type2_tag?shortest_path::spfa(n,1,n):
        shortest_path::dijkstra(n,1,n))<<'\n';
    return 0;
}
