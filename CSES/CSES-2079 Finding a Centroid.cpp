#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
int dfs(int u,int f=0){
    int hn=(G.size()-1)/2,res=0,ist=true;
    for(auto&i:G[u]){
        if(i==f) continue;
        auto d=dfs(i,u);ist&=(d<=hn);
        res+=d;
    }
    if(ist&&G.size()-res-2<=hn){
        cout<<u<<'\n';exit(0);}
    return res+1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1);
    return 0;
}