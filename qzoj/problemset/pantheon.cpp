#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k,p;cin>>n>>m>>k>>p;
    vector f(n+m+1,vector(n+1,vector(n+1,vector<lint>(k+1))));
    vector vis(n+m+1,vector(n+1,vector(n+1,vector<int>(k+1))));
    auto dfs=[&](auto __self,int ux,int uy,int vx,int vy,int c){
        if(ux+uy==n+m) return (lint)(c==k);
        c+=(ux==vx&&uy==vy);
        if(c>k) return 0ll;
        if(vis[ux+uy][ux][vx][c]) return f[ux+uy][ux][vx][c];
        vis[ux+uy][ux][vx][c]=true;
        auto&res=f[ux+uy][ux][vx][c];
        for(auto&[udx,udy]:{pair(0,1),pair(1,0)}) for(auto&[vdx,vdy]:{pair(0,1),pair(1,0)}){
            const auto nux=ux+udx,nuy=uy+udy;
            const auto nvx=vx+vdx,nvy=vy+vdy;
            if(nux<n+1&&nvx<n+1&&nuy<m+1&&nvy<m+1) (res+=__self(__self,nux,nuy,nvx,nvy,c))%=p;
        }
        return res;
    };
    cout<<dfs(dfs,0,0,0,0,-1)<<'\n';
    return 0;
}
