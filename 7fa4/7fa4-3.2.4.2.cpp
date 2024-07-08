#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
template<class comp>
int dfs(int u,bool less_tag,int&xs,vector<int>&ans){
    sort(G[u].begin(),G[u].end(),comp());
    ans[u]=xs;bool goin=false;
    for(auto&i:G[u]){
        xs=dfs<comp>(i,less_tag,xs,ans);goin=true;
    }
    if(!goin) xs=u;
    if(!less_tag) xs=u;
    return xs;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,f;cin>>n;G.resize(n+1);
    vector<int> A1(n+1),A2(n+1);
    cir(i,2,n+1) cin>>f,G[f].push_back(i);
    int xs=0;dfs<less<int>>(1,true,xs,A1);
    xs=0;dfs<greater<int>>(1,false,xs,A2);
    cir(i,1,n+1) cout<<A1[i]<<' '<<A2[i]<<'\n';
    return 0;
}