#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define IMPOSSIBLE \
    cout<<"IMPOSSIBLE\n",exit(0)
vector<vector<int>> G;
vector<int> vis,A;
void topsort(int u){
    if(vis[u]==1) return;
    if(vis[u]==-1) IMPOSSIBLE;
    vis[u]=-1;
    for(auto&i:G[u]) topsort(i);
    A.push_back(u);
    vis[u]=1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vis.resize(n+1);G.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    cir(i,1,n+1) if(!vis[i]) topsort(i);
    reverse(A.begin(),A.end());
    for(auto&i:A) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
