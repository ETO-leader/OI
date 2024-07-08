#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> tag,Ans;
void dfs(int u,int f=0,int cnt=0){
    cnt+=tag[u];Ans[u]=cnt;
    for(auto&i:G[u]) if(i!=f) dfs(i,u,cnt);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n);
    tag.resize(n);Ans.resize(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cir(i,0,m){
        int a,b;cin>>a>>b;tag[a]+=b;
    }
    dfs(0);
    for(auto&i:Ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}