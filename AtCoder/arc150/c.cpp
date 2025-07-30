#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;
        vector<vector<int>> vx(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            vx[u].emplace_back(v);
            vx[v].emplace_back(u);
        }
        vector<int> x(n),b(k);
        for(auto&i:x) cin>>i;
        for(auto&i:b) cin>>i;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
        q.emplace((x[0]==b[0]),0);
        vector<int> f(n,k+7),vis(n);
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&v:vx[u]) if(w+(w<k?(b[w]==x[v]):0)<f[v]){
                f[v]=w+(w<k?(b[w]==x[v]):0);
                q.emplace(f[v],v);
            }
        }
        cout<<(f[n-1]==k?"Yes":"No")<<'\n';
    }();
    return 0;
}
