#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<int>> gr;
vector<vector<int>> f,g;
auto dfs(int u,lint&ans,int fx=0)->int{
    f[u]={1};g[u]={0};
    for(auto&i:gr[u]) if(i!=fx){
        const auto hi=dfs(i,ans,u);
        if((int)(f[u].size())<hi+2){
            f[u].resize(hi+2);
            g[u].resize(hi+2);
        }
        cir(w,0,hi+2){
            if(w) ans+=f[i][w-1]*g[u][w];
            if(w+1<hi+1) ans+=f[u][w]*g[i][w+1];
        }
        cir(w,0,hi+2){
            if(w<hi+1) g[u][w+1]+=f[u][w+1]*f[i][w];
            if(w+1<hi+1) g[u][w]+=g[i][w+1];
        }
        cir(w,1,hi+2) f[u][w]+=f[i][w-1];
    }
    return (int)(f[u].size()-1);
}
auto init(int n){
    gr.resize(n+1);f.resize(n+1);g.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;init(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        gr[u].push_back(v);gr[v].push_back(u);
    }
    lint ans=0;dfs(1,ans);
    cout<<ans<<'\n';
    return 0;
}
