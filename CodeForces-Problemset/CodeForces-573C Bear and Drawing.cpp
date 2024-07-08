#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> G,csum;
VI cnode;
int nodetype(int u){
    auto&ci=csum[u];
    if(ci[4]||ci[3]||ci[2]>2) return 4;
    if(ci[2]==2) return 3;
    if(ci[2]||ci[1]||ci[0]>2) return 2;
    if(ci[0]>1) return 1;
    return 0;
}
int dfs(int u,int f=0){
    for(auto&i:G[u]) if(i!=f)
        csum[u][dfs(i,u)]++;
    return cnode[u]=nodetype(u);
}
void findyes(){
    cout<<"Yes\n";exit(0);
}
void rdfs(int u,int f=0,int t=-1){
    if(t>=0) csum[u][t]++;
    if(nodetype(u)<4) findyes();
    for(auto&i:G[u]) if(i!=f){
        csum[u][cnode[i]]--;
        rdfs(i,u,nodetype(u));
        csum[u][cnode[i]]++;
    }
    if(t>=0) csum[u][t]--;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    csum.assign(n+1,VI(5));
    cnode.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1);rdfs(1);
    cout<<"No\n";
    return 0;
}
