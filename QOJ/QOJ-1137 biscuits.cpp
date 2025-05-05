#include"biscuits.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using lint=long long;

lint count_tastiness(lint x,vector<lint> a){
    a.resize(60);
    const auto k=(int)(a.size());
    vector<__uint128_t> pre(k);
    cir(i,0,k) pre[i]=((__uint128_t)(a[i])<<i)+(i?pre[i-1]:0);
    cir(i,0,k) pre[i]/=x,pre[i]=min(pre[i],((__uint128_t)(1)<<(i+1))-1);
    unordered_map<lint,lint> f;
    f[(1ll<<k)-1]=1;
    for(auto i=k-1;~i;--i){
        unordered_map<lint,lint> g;
        for(auto&[x,w]:f) cir(c,0,2){
            const auto nw=(lint)(min<__uint128_t>(x,pre[i]));
            if(nw-(1ll<<i)*c>-1) g[nw-(1ll<<i)*c]+=w;
        }
        f=g;
    }
    return f[0]+f[1];
}
