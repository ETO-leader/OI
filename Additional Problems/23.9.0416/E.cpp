#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=998244353;
vector<vector<int>> D;
vector<vector<bool>> vis;
int cnx=0;
int dfs(int w,int k){
    if(w==k) return 1;
    if(w>k||((!w)&&k)) return 0;
    auto&d=D[w][k];
    if(vis[w][k]) return d;
    vis[w][k]=true;
    d=(dfs(w-1,k-1)+dfs(w*2,k))%MOD;
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int k,n;cin>>k>>n;
    D.assign(k+1,vector<int>(k+1));
    vis.assign(k+1,vector<bool>(k+1));
    cout<<dfs(n,k)<<'\n';
    return 0;
}
