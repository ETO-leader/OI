#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> G;
VI D,w,siz;
int dfs(int u,int f=0){
    if(f) D[u]=w[u];
    for(auto&i:G[u]) if(i!=f)
        siz[u]+=dfs(i,u)+2;
    sort(G[u].begin(),G[u].end(),[](int a,int b){
        return siz[a]-D[a]<siz[b]-D[b];});
    int pre=0;
    for(auto&i:G[u]) if(i!=f){
        D[u]=max(D[u],D[i]+pre+1);
        pre+=siz[i]+2;
    }
    return siz[u];
}
void init(int n){
    G.resize(n+1);D.resize(n+1);
    w.resize(n+1);siz.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;init(n);
    cir(i,1,n+1) cin>>w[i];
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1);
    cout<<max(D[1],w[1]+(n-1)*2)<<'\n';
    return 0;
}
