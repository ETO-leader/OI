#include<bits/stdc++.h>
using lint=long long;
#define cir(i,a,b) for(int i=a;i<b;++i)
#define assign(k,v) (k).assign(n+1,vector<lint>(n+1,v))
using namespace std;
vector<vector<lint>> V,D;
void floyd(int n){
    cir(i,1,n+1) D[i][i]=0;
    cir(k,1,n+1) cir(i,1,n+1) cir(j,1,n+1)
        D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
}
const lint _inf=1e18+7;
const lint _secinf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    assign(D,_inf);assign(V,_inf);
    cir(i,0,m){
        lint u,v,w;cin>>u>>v>>w;
        V[u][v]=min(V[u][v],w);V[v][u]=min(V[v][u],w);
    }
    D=V;floyd(n);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        if(D[u][v]>_secinf){cout<<-1<<'\n';continue;}
        cout<<D[u][v]<<'\n';
    }
    return 0;
}