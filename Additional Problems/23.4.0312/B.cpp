#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> H;
void dfs(int u,int f=0){
    H[u]=H[f]+1;
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    G.resize(n+1);H.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        cout<<(((H[u]+H[v])&1)
            ?"Road":"Town")<<'\n';
    }
    return 0;
}
