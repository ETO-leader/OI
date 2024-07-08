#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,id;};
vector<vector<edge>> G;
void dfs(int u,int&ans,int f=0,int rid=-1,int w=1){
    for(auto&[v,id]:G[u]) if(v!=f)
        dfs(v,ans,u,id,w+(id<rid));
    ans=max(ans,w);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;int ans=0;
        G.clear();G.resize(n+1);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            G[u].push_back({v,i});
            G[v].push_back({u,i});
        }
        dfs(1,ans);
        cout<<ans<<'\n';
    }
    return 0;
}
