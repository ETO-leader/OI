#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using graph=vector<vector<int>>;
int dfs(int u,graph&G,int&mx,int&mid,int f=0){
    int ret=1,mxi=0;
    for(auto&i:G[u]){
        if(i==f) continue;
        int d=dfs(i,G,mx,mid,u);
        ret+=d;mxi=max(mxi,d);
    }
    mxi=max(mxi,(int)(G.size()-1-ret));
    if(mx>mxi||mx==mxi&&mid>u) mx=mxi,mid=u;
    return ret;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,mx=1e9+7,mid=1;cin>>n;graph G(n+1);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            G[u].push_back(v),G[v].push_back(u);
        }
        dfs(1,G,mx,mid);
        cout<<mid<<' '<<mx<<'\n';
    }
    return 0;
}