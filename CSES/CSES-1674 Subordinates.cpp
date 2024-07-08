#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> ans;
int dfs(int u){
    for(auto&i:G[u]) ans[u]+=dfs(i);
    return ans[u]+1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,f;cin>>n;
    G.resize(n);ans.resize(n);
    cir(i,1,n) cin>>f,G[(--f)].push_back(i);
    dfs(0);
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}