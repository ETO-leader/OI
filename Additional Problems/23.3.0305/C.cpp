#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,p;};
vector<vector<edge>> G;
vector<bool> b;
using VI=vector<int>;
struct qnode{int u,tag;};
const int _inf=1e9+7;
int bfs(int ux,int vx){
    vector<VI> D(2,VI(G.size(),_inf)),
        vis(2,VI(G.size()));
    queue<qnode> q;q.push({ux,0}),D[0][ux]=0;
    if(b[ux]) q.push({ux,1}),D[1][ux]=0;
    while(!q.empty()){
        auto [u,ch]=q.front();q.pop();
        auto d=D[ch][u];
        if(vis[ch][u]) continue;
        vis[ch][u]=true;
        //在当前变化情况 & 1 = cg 的情况下走向周围的点
        auto wentinto=[&](int cg){
            for(auto&[v,p]:G[u]){
                if((p^cg)&&!vis[cg][v]
                    &&D[cg][v]>d+1)
                    D[cg][v]=d+1,q.push({v,cg});
            }
        };
        wentinto(ch);
        if(b[u]) wentinto(ch^1);
    }
    return min(D[0][vx],D[1][vx])==_inf?
        -1:min(D[0][vx],D[1][vx]);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    G.resize(n+1);b.resize(n+1);
    cir(i,0,m){
        int u,v,tag;cin>>u>>v>>tag;
        G[u].push_back({v,tag});
        G[v].push_back({u,tag});
    }
    cir(i,0,k){
        int p;cin>>p;b[p]=true;
    }
    cout<<bfs(1,n)<<'\n';
    return 0;
}
