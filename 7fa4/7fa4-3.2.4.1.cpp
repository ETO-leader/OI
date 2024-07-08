#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
unordered_map<int,int> colcnt;
vector<int> Ans,col,isl;
void dfs(int u,int f=0){
    colcnt[col[u]]++;
    for(auto&i:G[u]) if(i!=f) dfs(i,u),isl[u]=true;
    if((isl[u]=(!isl[u]))) Ans[u]=colcnt.size();
    if(!(--colcnt[col[u]])) colcnt.erase(col[u]);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n);isl.resize(n);
    Ans.resize(n);col.resize(n);
    cir(i,1,n){
        int nxt;cin>>nxt>>col[i];
        G[nxt].push_back(i);G[i].push_back(nxt);
    }
    dfs(0);
    cir(i,0,n) if(isl[i]) cout<<i<<' '<<Ans[i]<<'\n';
    return 0;
}
