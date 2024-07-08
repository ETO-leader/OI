#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge_t{int u,v;lint w;};
struct edge{int v;lint w;};
const lint _inf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<edge_t> E(m);
    vector<vector<lint>> dist(
        n+1,vector<lint>(n+1,_inf));
    cir(i,1,n+1) dist[i][i]=0;
    for(auto&[u,v,w]:E){ 
        cin>>u>>v>>w;
        dist[u][v]=dist[v][u]=w;
    }
    [&](){
        cir(k,1,n+1) cir(i,1,n+1) cir(j,1,n+1)
            dist[i][j]=
                min(dist[i][j],dist[i][k]+dist[k][j]);
    }();
    lint cnx=0;
    for(auto&[u,v,w]:E){
        cir(i,1,n+1) if(i!=u&&i!=v){
            if(dist[u][i]+dist[i][v]<=w){
                ++cnx;break;
            }
        }
    }
    cout<<cnx<<'\n';
    return 0;
}
