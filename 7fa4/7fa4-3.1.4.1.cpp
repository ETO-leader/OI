#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define assign(k,v) (k).assign(n+1,vector<int>(n+1,v))
using namespace std;
vector<vector<int>> V,D,F;
void floyd(int n){
    cir(i,1,n+1) D[i][i]=0;
    cir(k,1,n+1) cir(i,1,n+1) cir(j,1,n+1)
        D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
}
const int _inf=1e9+7;
const int _secinf=1e8+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;assign(F,_inf);
    assign(D,_inf);assign(V,_inf);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        V[u][v]=min(V[u][v],w);
    }
    D=V;floyd(n);
    cir(i,1,n+1) cir(j,1,n+1) cir(k,1,n+1){
        if(i!=k&&D[i][j]==D[k][j]+V[i][k])
            F[i][j]=min(F[i][j],k);
    }
    cir(i,0,q){
        int u,v;cin>>u>>v;
        if(D[u][v]>_secinf){cout<<-1<<'\n';continue;}
        cout<<D[u][v]<<' '<<u<<' ';
        while(u!=v) u=F[u][v],cout<<u<<' ';
        cout<<'\n';
    }
    return 0;
}
