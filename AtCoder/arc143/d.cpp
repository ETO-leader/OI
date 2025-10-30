#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<int> a(m),b(m);
    for(auto&x:a) cin>>x,--x;
    for(auto&x:b) cin>>x,--x;
    vector<vector<pair<int,int>>> gr(n);
    cir(i,0,m){
        gr[a[i]].emplace_back(b[i],i);
        gr[b[i]].emplace_back(a[i],i);
    }
    vector<int> vis(n),evis(m);
    string ans(m,'0');
    auto dfs=[&](auto __self,int u)->void {
        vis[u]=true;
        for(auto&[v,id]:gr[u]) if(!evis[id]){
            evis[id]=true;
            ans[id]='0'+(u==b[id]);
            if(!vis[v]) __self(__self,v);
        }
    };
    cir(u,0,n) if(!vis[u]) dfs(dfs,u);
    cout<<ans<<'\n';
    return 0;
}
