#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> G,D;
VI state;
void dfs(int u,int f=0){
    auto&d=D[u];
    int cnx=0;
    for(auto&i:G[u]) if(i!=f){
        dfs(i,u);
        if(!cnx) d[0]=D[i][0];
        if(!cnx) d[1]=D[i][1];
        auto dx=d;
        if(cnx) d[0]=max(dx[0]+D[i][0],dx[1]+D[i][1]);
        if(cnx) d[1]=max(dx[0]+D[i][1],dx[1]+D[i][0]);
        ++cnx;
    }
    d[0]+=state[u];d[1]+=(!state[u]);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;state.resize(n+1);
    G.resize(n+1);D.assign(n+1,VI(2));
    cir(i,1,n+1) cin>>state[i];
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1);
    cout<<max(D[1][0],D[1][1])<<'\n';
    return 0;
}
