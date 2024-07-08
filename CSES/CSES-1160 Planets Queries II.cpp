#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define CANNOT {cout<<"-1\n";continue;}
using namespace std;
vector<vector<int>> UP;
vector<int> vis,H;
void dfs(int u,int f=0){
    if(vis[u]) return;
    vis[u]=true;dfs(UP[u][0],u);
    H[u]=H[UP[u][0]]+1;
}
int jump(int u,int k,const int HT){
    if(k<0) return -1;
    cir(i,0,HT) if((1<<i)&k) u=UP[u][i];
    return u;
}
void UPinit(int n,int HT){
    cir(i,1,HT) cir(j,1,n+1)
        UP[j][i]=UP[UP[j][i-1]][i-1];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;const int HT=log2(n)+2;
    vis.resize(n+1);H.resize(n+1);
    UP.assign(n+1,vector<int>(HT));
    cir(i,1,n+1) cin>>UP[i][0];
    UPinit(n,HT);
    cir(i,1,n+1) if(!vis[i]) dfs(i);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        auto Fu=jump(u,H[u],HT);
        if(jump(u,H[u]-H[v],HT)!=v&&
            jump(Fu,H[Fu]-H[v],HT)!=v) CANNOT;
        if(jump(u,H[u]-H[v],HT)==v)
            cout<<H[u]-H[v]<<'\n';
        else cout<<H[u]+H[Fu]-H[v]<<'\n';
    }
    return 0;
}
