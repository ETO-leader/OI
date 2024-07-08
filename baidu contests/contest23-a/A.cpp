#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e15+7;
vector<vector<int>> G;
auto bfs(int ux,lint ew){
    VI D(G.size(),_inf);
    vector<bool> vis(G.size());
    queue<int> q;q.push(ux);
    vis[ux]=true;D[ux]=0;
    while(!q.empty()){
        const int u=q.front();q.pop();
        for(auto&i:G[u]) if(!vis[i]){
            vis[i]=true;D[i]=D[u]+ew;
            q.push(i);
        }
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint te,fe,s;cin>>te>>fe>>s;
    int t,f,n,m;cin>>t>>f>>n>>m;
    G.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto dt=bfs(t,te);
    auto df=bfs(f,fe);
    auto sw=bfs(n,te+fe-s);
    lint ans=_inf;
    cir(i,1,n+1){
        ans=min(ans,dt[i]+df[i]+sw[i]);
    }
    cout<<(ans==_inf?-1:ans)<<'\n';
    return 0;
}
