#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
using heap=__gnu_pbds::priority_queue<
    T,less<T>,__gnu_pbds::pairing_heap_tag>;
template<typename T,T _inf>
class graph{
private:
    struct edge{int v;T w;};
    vector<T> dis;
    vector<vector<edge>> G;
    vector<vector<T>> D;
    struct edge_t{int u,v;T w;};
    vector<edge_t> es;
    void builx(){
        for(auto&i:G) i.clear();
        cir(i,1,G.size()) G[0].push_back({i,0});
        for(auto&[u,v,w]:es)
            G[u].push_back({v,w-dis[v]+dis[u]});
    }
    void spfa(){
        queue<int> q;q.push(0);
        builx();
        fill(dis.begin(),dis.end(),_inf);
        dis[0]=0;
        vector<bool> inq(G.size());
        while(!q.empty()){
            auto u=q.front();q.pop();
            inq[u]=false;
            for(auto&[v,w]:G[u]){
                if(dis[u]+w>=dis[v]) continue;
                dis[v]=dis[u]+w;
                if(!inq[v]) q.push(v);
            }
        }
    }
    struct heapnode{
        int u;T w;
        bool operator<(const heapnode&n) const{
            return w>n.w;
        }
    };
    void dijkstra(int s){
        heap<heapnode> q;q.push({s,0});
        vector<bool> vis(G.size());
        D[s][s]=0;
        while(!q.empty()){
            auto [u,w]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wi]:G[u]){
                if(!vis[v]&&D[s][v]>w+wi){
                    D[s][v]=w+wi;q.push({v,w+wi});
                }
            }
        }
    }
    int nx;
public:
    void insert(int u,int v,T w){
        es.push_back({u,v,w});}
    graph(int _x):G(_x+1),dis(_x+1),nx(_x+1),
        D(_x+1,vector<T>(_x+1,_inf)){}
    void jonhson(){
        spfa();builx();
        cir(i,1,nx) dijkstra(i);
    }
    T operator()(int a,int b){return D[a][b]-dis[a]+dis[b];}
};
using lint=long long;
const lint _inf=1e16+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;graph<lint,_inf> G(n+1);
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        G.insert(u,v,w);
    }
    G.jonhson();
    cir(i,1,n+1){
        cir(j,1,n+1){
            if(G(i,j)>=_inf/10000) cout<<"inf ";
            else cout<<G(i,j)<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
