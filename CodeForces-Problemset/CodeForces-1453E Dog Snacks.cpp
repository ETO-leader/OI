#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> G;
bool isroot(int u){return u==1;}
int dfs(int u,int&ans,int f=0){
    VI vx;
    for(auto&i:G[u]) if(i!=f)
        vx.push_back(dfs(i,ans,u));
    sort(vx.begin(),vx.end());
    ans=max((vx.empty()?0:vx[0]),ans);
    auto getbk=[&](){
        int r=vx.back();vx.pop_back();
        return r;
    };
    if(vx.size()>1){
        if(isroot(u)){
            ans=max({ans,getbk(),getbk()+1});
        }else{
            ans=max(ans,getbk()+1);
        }
    }
    return (vx.empty()?0:vx[0])+1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        G.clear();G.resize(n+1);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int ans=0;dfs(1,ans);
        cout<<ans<<'\n';
    }
    return 0;
}
