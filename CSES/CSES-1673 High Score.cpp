#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define IMPOSSIBLE cout<<"-1\n",exit(0)
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
const lint _inf=1e18+7;
vector<int> Cr1,Cr2,vis,Ct1,Ctn;
void dfs(int u,vector<int>&R){
    R[u]=true;vis[u]=true;
    for(auto&i:G[u]) if(!vis[i.v]) dfs(i.v,R);
}
void going(int u,int rt,int n){
    if(u==1) Ct1[rt]=true;
    if(u==n) Ctn[rt]=true;
    vis[u]=true;
    for(auto&i:G[u]) if(!vis[i.v]) going(i.v,rt,n);
}
vector<lint> SPFA(int u){
    vector<lint> vist(G.size()),D(G.size(),_inf);
    int n=G.size()-1;D[u]=0;
    queue<int> q;q.push(u);
    while(!q.empty()){
        auto f=q.front();q.pop();
        if((++vist[f])>=n&&((Cr1[f]&&Ctn[f])||
            (Ct1[f]&&Cr1[f])||(Ctn[f]&&Cr2[f]))) IMPOSSIBLE;
        if(vist[f]>=n) continue;
        for(auto&i:G[f]){
            if(D[f]+i.w<D[i.v]&&vist[i.v]<n)
                q.push(i.v),D[i.v]=D[f]+i.w;
        }
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vis.resize(n+1);
    Cr1.resize(n+1);Cr2.resize(n+1);G.resize(n+1);
    Ct1.resize(n+1);Ctn.resize(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,-w});
    }
    dfs(1,Cr1);fill(vis.begin(),vis.end(),false);
    dfs(n,Cr2);
    cir(i,0,n+1)
        fill(vis.begin(),vis.end(),false),going(i,i,n);
    auto D=SPFA(1);
    cout<<(-D[n])<<'\n';
    return 0;
}