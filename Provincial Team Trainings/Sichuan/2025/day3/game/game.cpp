#include"game.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

int ssiz;
map<int,int> revid;

vector<pair<int,int>> init(vector<pair<int,int>> qwq,int n,int m,int k,int q,int qlim){
    ssiz=min(20,n);
    vector<pair<int,int>> res;
    cir(i,0,ssiz) cir(j,i+1,ssiz) res.emplace_back(i,j);
    for(auto&[u,v]:qwq) if(u>ssiz-1&&v>ssiz-1) res.emplace_back(u,v);
    vector<vector<int>> cnts(21);
    cir(i,0,1<<(ssiz)) cnts[__builtin_popcount(i)].emplace_back(i);
    vector<int> ls;
    for(auto&x:cnts) for(auto&i:x) ls.emplace_back(i);
    auto pos=0;
    cir(u,ssiz,n){
        revid[ls[pos]]=u;
        cir(i,0,ssiz) if((ls[pos]>>i)&1) res.emplace_back(u,i);
        res.emplace_back(u,u);
        ++pos;
    }
    return res;
}

int ask(){
    auto res=0;
    cir(i,0,ssiz){
        const auto u=play({i});
        if(u==-1) return i;
        if(u) res|=(1<<i);
    }
    return revid[res];
}

