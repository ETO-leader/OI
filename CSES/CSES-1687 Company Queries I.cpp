#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G,F;
int HT;
void dfs(int u,int f=0){
    F[u][0]=f;
    cir(i,1,HT+1) F[u][i]=F[F[u][i-1]][i-1];
    for(auto&i:G[u]) dfs(i,u);
}
int jump(int u,int k){
    cir(i,0,HT+1) if((1<<i)&k) u=F[u][i];
    return (!u?-1:u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;G.resize(n+1);
    HT=log2(n)+2;
    F.assign(n+1,vector<int>(HT+1));
    cir(i,2,n+1){
        int f;cin>>f;
        G[f].push_back(i);
    }
    dfs(1);
    cir(i,0,q){
        int u,k;cin>>u>>k;
        cout<<jump(u,k)<<'\n';
    }
    return 0;
}