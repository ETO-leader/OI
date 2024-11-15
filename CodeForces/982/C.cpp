#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        vector<lint> wx(n);
        cir(i,0,n) wx[i]=a[i]+i;
        map<lint,lint> id;
        cir(i,0,n) id.emplace(wx[i],0),id.emplace(wx[i]+i,0);
        id.emplace(n,0);
        for(auto c=-1;auto&[a,b]:id) b=++c;
        const auto m=(int)(id.size());
        vector<vector<int>> to(n+m);
        cir(i,0,n){
            to[id[wx[i]]].push_back(i+m);
            to[i+m].push_back(id[wx[i]+i]);
        }
        vector<int> vis(n+m);
        auto dfs=[&](auto __self,int u)->void {
            if(vis[u]) return;
            vis[u]=true;
            for(auto&i:to[u]) __self(__self,i);
        };
        dfs(dfs,id[n]);
        auto ans=(lint)(n);
        for(auto&[x,idx]:id) if(vis[idx]) ans=max(ans,x);
        println("{}",ans);
    }();
    return 0;
}
