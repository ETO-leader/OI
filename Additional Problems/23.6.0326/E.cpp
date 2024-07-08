#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
vector<vector<lint>> mx;
vector<lint> ans,dx;
void dfs(int u,int f=0){
    for(auto&[v,w]:G[u]) if(v!=f){
        dfs(v,u);
        mx[u].push_back(max(mx[v][0],dx[v])+w);
    }
    while(mx[u].size()<2) mx[u].push_back(0);
    sort(mx[u].begin(),mx[u].end(),greater<lint>());
    while(mx[u].size()>2) mx[u].pop_back();
}
void runans(int u,int f=0,lint wi=0){
    ans[u]=max(mx[u][0],wi);
    for(auto&[v,w]:G[u]) if(v!=f){
        lint ax=max({(mx[u][0]==max(mx[v][0],dx[v])+w?
            mx[u][1]:mx[u][0]),wi,dx[u]})+w;
        runans(v,u,ax);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);dx.resize(n+1);
    mx.resize(n+1);ans.resize(n+1);
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    cir(i,1,n+1) cin>>dx[i];
    dfs(1);runans(1);
    cir(i,1,n+1) cout<<ans[i]<<'\n';
    return 0;
}
