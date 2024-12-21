#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
vector<vector<int>> G,Mx;
vector<int> L,Ct;int mn=_inf;
void dfs1(int u,int f=0){
    for(auto&i:G[u]) if(i!=f){
        dfs1(i,u);Mx[u].push_back(Mx[i][0]+1);
    }
    while(Mx[u].size()<2) Mx[u].push_back(0);
    sort(Mx[u].begin(),Mx[u].end(),greater<int>());
}
void dfs2(int u,int f=0){
    auto&mx=Mx[u];
    if(u) mx.push_back(Mx[f][0]-1==mx[0]?Mx[f][1]+1:Mx[f][0]+1);
    sort(Mx[u].begin(),Mx[u].end(),greater<int>());
    L[u]=mx[0]+mx[1];mn=(mn>mx[0]?Ct.clear(),mx[0]:mn);
    if(mn==mx[0]) Ct.push_back(u);
    for(auto&i:G[u]) if(i!=f) dfs2(i,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n);Ct.resize(n);
    Mx.resize(n);L.resize(n);
    cir(i,1,n){
        int f;cin>>f;
        G[f].push_back(i),G[i].push_back(f);
    }
    dfs1(0);dfs2(0);
    cout<<*max_element(L.begin(),L.end())<<'\n';
    sort(Ct.begin(),Ct.end());
    for(auto&i:Ct) cout<<i<<' ';cout<<'\n';
    return 0;
}