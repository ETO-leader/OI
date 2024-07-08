#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define res(x) (x).resize(n+1)
using namespace std;
using lint=long long;
struct edge{int v,w;};
vector<vector<edge>> G;
vector<vector<lint>> Mx;
vector<lint> D,C,Nx,A,Ax;
lint dfs1(int u,int f=0){
    Nx[u]=(bool)(C[u]);
    for(auto&i:G[u]) if(i.v!=f){
        D[u]+=dfs1(i.v,u)+i.w*2*Nx[i.v];
        Nx[u]|=Nx[i.v];
        if(Nx[i.v]) Mx[u].push_back(Mx[i.v][0]+i.w);
    }
    sort(Mx[u].begin(),Mx[u].end(),greater<int>());
    while(Mx[u].size()<2) Mx[u].push_back(0);
    return D[u];
}
void dfs2(int u,lint w=0LL,int f=0){
    A[u]=D[u]-Mx[u][0];Ax[u]=D[u];
    if(u!=1){
        Mx[u].push_back((Mx[f][0]-w
            ==Mx[u][0]?Mx[f][1]+w:Mx[f][0]+w));
        sort(Mx[u].begin(),Mx[u].end(),greater<int>());
        Mx[u].pop_back();
        Ax[u]=Ax[f]+w*2*(!Nx[u]);
        A[u]=Ax[u]-Mx[u].front();
    }
    for(auto&i:G[u]) if(i.v!=f) dfs2(i.v,i.w,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;res(A);res(C);
    res(G);res(D);res(Mx);res(Nx);res(Ax);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    cir(i,0,m){
        int ci;cin>>ci;C[ci]++;
    }
    dfs1(1);dfs2(1);
    cir(i,1,n+1) cout<<A[i]<<'\n';
    return 0;
}