#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct quary{int d,id;};
vector<vector<quary>> Q;
vector<vector<int>> G;
vector<int> col,cnx,ans;
void dfs(int u,int h=1){
    vector<int> qx;
    cnx[h]^=(1<<col[u]);
    for(auto&i:Q[u]) qx.push_back(cnx[i.d]);
    for(auto&i:G[u]) dfs(i,h+1);
    cir(i,0,Q[u].size()){
        auto idx=Q[u][i].id;
        ans[idx]=qx[i]^cnx[Q[u][i].d];
    }
}
void scan(int n,int q){
    cir(i,2,n+1){
        int f;cin>>f;G[f].push_back(i);
    }
    string s;cin>>s;
    cir(i,0,n) col[i+1]=s[i]-'a';
    cir(i,0,q){
        int u,h;cin>>u>>h;
        Q[u].push_back({h,i});
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;G.resize(n+1);
    Q.resize(n+1);cnx.resize(n+1);
    col.resize(n+1);ans.resize(q);
    scan(n,q);dfs(1);
    for(auto&i:ans) cout<<(__builtin_popcount(i)
        >1?"No":"Yes")<<'\n';
    return 0;
}
