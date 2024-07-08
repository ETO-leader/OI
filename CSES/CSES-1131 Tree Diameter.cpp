#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
int dfs(int u,int&ans,int f=0){
    int mx=0,sec=0;
    for(auto&i:G[u]) if(i!=f){
        auto d=dfs(i,ans,u);
        if(d>=mx) swap(mx,sec),mx=d;
        else if(d>sec) sec=d;
    }
    ans=max(ans,mx+sec);
    return mx+1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    int ans=0;dfs(1,ans);
    cout<<ans<<'\n';
    return 0;
}