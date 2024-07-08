#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> vis,inn,tps;
vector<pair<int,int>> Ans;
vector<vector<int>> G;
vector<pair<int,pair<int,int>>> Es;
int cnt=0;
bool dfs(int u){
    vis[u]=-1;
    auto res=true;
    for(auto&i:G[u])
        if(!vis[i]) res&=dfs(i);
        else if(vis[i]==-1) return false;
    return vis[u]=1,tps[u]=++cnt,res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    Ans.resize(m);vis.resize(n+1);
    inn.resize(n+1);tps.resize(n+1);
    cir(i,0,m){
        int op,u,v;cin>>op>>u>>v;
        if(!op) Es.push_back({u,{v,i}});
        else G[u].push_back(v),Ans[i]={u,v},inn[v]++;
    }
    auto res=true;
    cir(i,1,n+1) if(!vis[i]&&!inn[i]) res&=dfs(i);
    if(!res){cout<<"NO\n";exit(0);}
    cout<<"YES\n";
    for(auto&i:Es){
        auto u=i.first,v=i.second.first,
            id=i.second.second;
        if(tps[u]<tps[v]) swap(u,v);
        Ans[id]={u,v};
    }
    for(auto&i:Ans) cout<<i.first<<' '<<i.second<<'\n';
    return 0;
}