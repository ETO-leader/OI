#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,vis,rid;};
vector<vector<edge>> G;
stack<int> Node;
vector<int> vis;
void print(int u){
    stringstream ss;int cnt=2;
    ss<<'\n'<<u<<' ';
    while(Node.top()!=u)
        ss<<Node.top()<<' ',Node.pop(),++cnt;
    ss<<u<<'\n';
    cout<<cnt<<ss.str();
}
void dfs(int u){
    if(vis[u]==-1) print(u),exit(0);
    vis[u]=-1;Node.push(u);
    for(auto&i:G[u]) if(!i.vis&&vis[i.v]!=1){
        i.vis=true;G[i.v][i.rid].vis=true;
        dfs(i.v);
        i.vis=false;G[i.v][i.rid].vis=false;
    }
    vis[u]=1;Node.pop();
} 
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    G.resize(n+1);vis.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back({v,false,(int)(G[v].size())});
        G[v].push_back({u,false,(int)(G[u].size()-1)});
    }
    cir(i,1,n+1) if(!vis[i]) dfs(i);
    cout<<"IMPOSSIBLE\n";
    return 0;
}