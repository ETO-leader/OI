#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using rbt=tree<T,null_type,greater<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
vector<vector<int>> G;
unordered_map<int,int> Ap;
vector<int> Ans,col;
rbt<int> rb;int cnt=0;
void dfs(int u,int f=0){
    int cx=(++cnt);
    if(Ap.count(col[u])) rb.erase(Ap[col[u]]);
    Ap[col[u]]=cx;rb.insert(Ap[col[u]]);
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
    Ans[u]=rb.order_of_key(cx-1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;Ans.resize(n+1);
    G.resize(n+1);col.resize(n+1);
    cir(i,1,n+1) cin>>col[i];
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1);
    cir(i,1,n+1) cout<<Ans[i]<<' ';
    cout<<'\n';
    return 0;
}