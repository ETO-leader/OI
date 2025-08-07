#include"worldmap.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

vector<vector<int>> create_map(int N,int M,vector<int> A,vector<int> B){
    vector<vector<int>> vx(N);
    cir(i,0,M) vx[A[i]-1].emplace_back(B[i]-1),vx[B[i]-1].emplace_back(A[i]-1);
    vector res(N*2,vector<int>(N*2));
    auto cnt=0;
    auto colorl=[&](int x,int val){
        cir(i,0,x){
            auto y=(cnt>N*2-1?cnt-N*2+1:0);
            for(auto x=cnt-y;(~x)&&(y<N*2);--x,++y) res[x][y]=val;
            ++cnt;
        }
    };
    vector<int> vis(N);
    auto dfs=[&](auto __self,int u)->void {
        vis[u]=true;
        colorl(3,u+1);
        auto sum=cnt-2;
        auto y=(sum>N*2-1?sum-N*2+1:0);
        for(auto&v:vx[u]) if(vis[v]){
            const auto x=sum-y;
            res[x][y]=v+1;
            ++y;
        }
        for(auto&v:vx[u]) if(!vis[v]){
            __self(__self,v);
            colorl(1,u+1);
        }
    };
    dfs(dfs,0);
    return res;
}
