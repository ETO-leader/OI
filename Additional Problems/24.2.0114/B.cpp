#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> gr;
VI lf,rg,vis;
auto dfs(int u){
    if(vis[u]<0) [[unlikely]] throw exception();
    if(vis[u]) return;
    vis[u]=-1;
    for(auto&i:gr[u]) dfs(i);
    vis[u]=1;
}
//Graph is a DAG
auto check(){
    VI cnt(gr.size()),inx(gr.size());
    for(auto&i:gr) for(auto&j:i) ++inx[j];
    queue<int> q;stack<int> upd;
    cir(i,0,(int)(gr.size())) if(!inx[i])
        q.push(i);
    while(!q.empty()){
        auto u=q.front();q.pop();
        upd.push(u);
        for(auto&i:gr[u]){
            lf[i]=max(lf[i],lf[u]+1);
            if(!(--inx[i])){
                q.push(i);
            }
        }
    }
    while(!upd.empty()){
        auto u=upd.top();upd.pop();
        VI kx;kx.reserve(gr[u].size());
        for(auto&i:gr[u]){
            kx.push_back(rg[i]);
            rg[u]=min(rg[u],rg[i]-1);
        }
    }
}
auto init(int n){
    gr.resize(n+1);lf.resize(n+1);
    rg.resize(n+1);vis.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;init(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        gr[u].push_back(v);
    }
    cir(i,1,n+1) cin>>lf[i]>>rg[i];
    vector<vector<pair<int,int>>> lfs(n+1);
    VI ans(n);
    try{
        cir(i,1,n+1) if(!vis[i]) dfs(i);
        check();
        cir(i,1,n+1){
            lfs[lf[i]].push_back({rg[i],i-1});
            if(lf[i]>rg[i]) [[unlikely]] throw exception();
        }
        priority_queue<pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>> qx;
        cir(i,1,n+1){
            for(auto&x:lfs[i]) qx.push(x);
            if(qx.empty()) [[unlikely]] throw exception();
            if(qx.top().first<i) [[unlikely]]
                throw exception();
            ans[qx.top().second]=i;
            qx.pop();
        } 
    }catch(exception){
        exit((cout<<"No\n",false));
    }
    cout<<"Yes\n";
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
