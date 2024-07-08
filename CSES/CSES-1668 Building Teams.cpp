#include<bits/stdc++.h>
#define NoSolution() cout<<"IMPOSSIBLE\n",exit(0);
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> Tag,vis;
void init(int u,int col=0){
    vis[u]=true;Tag[u]=col;
    for(auto&i:G[u]){
        if(vis[i]&&Tag[i]!=col^1) NoSolution();
        if(!vis[i]) init(i,col^1);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    Tag.resize(n+1);vis.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cir(i,1,n+1) if(!vis[i]) init(i);
    cir(i,1,n+1) cout<<Tag[i]+1<<' ';
    cout<<'\n';
    return 0;
}
