#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> bfs(){
    queue<int> q;q.push(1);
    vector<int> vis(G.size()),F(G.size(),-1);
    vis[1]=true;
    while(!q.empty()){
        auto f=q.front();q.pop();
        for(auto&i:G[f]) if(!vis[i])
            vis[i]=true,F[i]=f,q.push(i);
    }
    return F;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    auto F=bfs();vector<int> Ps;
    if(F[n]==-1){cout<<"IMPOSSIBLE\n";exit(0);}
    auto u=n;Ps.push_back(u);
    while(u!=1) Ps.push_back(F[u]),u=F[u];
    cout<<Ps.size()<<'\n';
    while(!Ps.empty()) cout<<Ps.back()<<' ',Ps.pop_back();
    cout<<'\n';
    return 0;
}