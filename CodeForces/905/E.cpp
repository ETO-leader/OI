#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
static constexpr int _inf=1e9+7;
struct edge{int v;int t;};
vector<vector<edge>> G;
struct heapnode{
    int u,w;
    bool operator<(const heapnode&x) const{
        return w>x.w;
    }
};
int bfs(vector<deque<int>> nxt,int n){
    VI D(n+1,_inf),vis(n+1);D[1]=0;
    priority_queue<heapnode> q;q.push({1,0});
    while(!q.empty()){
        auto[u,w]=q.top();q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(auto&[v,wi]:G[u]){
            while((!nxt[wi].empty())&&nxt[wi].
                front()<w+1) nxt[wi].pop_front();
            if(nxt[wi].empty()) continue;
            if(D[v]>nxt[wi].front()){
                D[v]=nxt[wi].front();
                q.push({v,nxt[wi].front()});
            }
        }
    }
    return D[n];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,t;cin>>n>>t;G.resize(n+1);
    vector<deque<int>> nxt(t);
    cir(i,0,t){
        int mi;cin>>mi;
        cir(cx,0,mi){
            int u,v;cin>>u>>v;
            G[u].push_back({v,i});
            G[v].push_back({u,i});
        }
    }
    int m;cin>>m;
    cir(i,0,m){
        int u;cin>>u;
        nxt[u-1].push_back(i+1);
    }
    int ans=bfs(nxt,n);
    cout<<(ans==_inf?-1:ans)<<'\n';
    return 0;
}
