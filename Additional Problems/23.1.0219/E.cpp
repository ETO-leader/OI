#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
namespace part1{
    void dfs(int u,vector<bool>&vis){
        vis[u]=true;
        for(auto&i:G[u]) if(!vis[i])
            cout<<u<<' '<<i<<'\n',dfs(i,vis);
    }
    void run(){
        vector<bool> vis(G.size());
        dfs(1,vis);
    }
}
namespace part2{
    void bfs(){
        queue<int> q;q.push(1);
        vector<bool> vis(G.size());
        vis[1]=true;
        while(!q.empty()){
            auto u=q.front();q.pop();
            for(auto&i:G[u]){
                if(vis[i]) continue;
                vis[i]=true;q.push(i);
                cout<<u<<' '<<i<<'\n';
            }
        }
    }
    void run(){bfs();}
}
namespace scanner{
    pair<int,int> read_in(){
        int n,m;cin>>n>>m;
        G.resize(n+1);
        cir(i,0,m){
            int u,v;cin>>u>>v;
            G[u].push_back(v);G[v].push_back(u);
        }
        return {n,m};
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    scanner::read_in();
    part1::run();
    part2::run();
    return 0;
}
