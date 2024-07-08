#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
constexpr int _inf=1e9+7;
vector<VI> G,D;
VI c;
void dfs(int u,int f=0){
    //is leaf
    if(u<c.size()){
        D[u][c[u]]=0;D[u][2]=1;
        D[u][c[u]^1]=_inf;
        return;
    }
    //else
    int cw=1,cb=1;
    for(auto&i:G[u]) if(i!=f){
        dfs(i,u);
        cw+=min(D[i][2],D[i][0]);
        cb+=min(D[i][2],D[i][1]);
        D[u][2]+=D[i][2];
        D[u][0]+=min(D[i][2],D[i][0]);
        D[u][1]+=min(D[i][2],D[i][1]);
    }
    D[u][2]=min({D[u][2],cw,cb});
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>m>>n;G.resize(m+1);
    c.resize(n+1);D.assign(m+1,VI(3));
    cir(i,1,n+1) cin>>c[i];
    cir(i,0,m-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    const int rt=n+1;
    dfs(rt);
    cout<<D[rt][2]<<'\n';
    return 0;
}
