#include"fun.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

vector<int> createFunTour(int n,int q){
    assert(q==400000);
    const auto rt=[&]{
        vector<int> siz(n);
        siz[0]=n-attractionsBehind(1,0);
        cir(i,1,n) siz[i]=n-attractionsBehind(0,i);
        auto res=pair(-1,-1);
        cir(i,0,n) if(siz[i]<n/2+1) res=max(res,pair(siz[i],i));
        return res.second;
    }();
    // get all nodes' height
    vector<int> dep(n);
    cir(i,0,n) dep[i]=hoursRequired(rt,i);
    vector<int> ux;
    vector<int> id(n);
    iota(id.begin(),id.end(),0);
    ranges::sort(id,[&](auto u,auto v){return dep[u]<dep[v];});
    vector<int> ans;
    cir(i,0,n) if(dep[i]==1) ux.emplace_back(i);
    const auto m=(int)(ux.size());
    vector<priority_queue<pair<int,int>>> stcu(m);
    // node information
    auto insubtree=[&](int x,int u){
        return hoursRequired(ux[x],u)<dep[u];
    };
    vector<int> urt(n);
    cir(i,0,n) if(i!=rt){
        if(insubtree(0,i)) stcu[urt[i]=0].emplace(dep[i],i);
        else if(insubtree(1,i)) stcu[urt[i]=1].emplace(dep[i],i);
        else stcu[urt[i]=2].emplace(dep[i],i);
    }
    // construct
    const auto u=id.back();
    ans.emplace_back(u);
    auto cur=urt[u];
    vector<pair<int,int>> repush;
    while(stcu[cur].top().second!=u){
        repush.emplace_back(stcu[cur].top());
        stcu[cur].pop();
    }
    stcu[cur].pop();
    for(auto&x:repush) stcu[cur].emplace(x);
    auto spccase=[&](vector<int> ul,vector<int> ur){
        priority_queue<pair<int,int>> lf,rg;
        auto ldep=(ans.size()>1?dep[ans[ans.size()-2]]:-n);
        if()
        for(auto&u:ul){
            while(!stcu[u].empty()) lf.emplace(stcu[u].top()),stcu[u].pop();
        }
        for(auto&u:ur){
            while(!stcu[u].empty()) rg.emplace(stcu[u].top()),stcu[u].pop();
        }
        while(!lf.empty()){
            ans.emplace_back(lf.top().second);
            lf.pop();
            swap(lf,rg);
        }
        ans.emplace_back(rt);
    };
    auto usiz=[&](int u){return (int)(stcu[u].size());};
    auto nusiz=[&](int u){
        auto cnt=0;
        cir(i,0,m) if(i!=u) cnt+=(int)(stcu[i].size());
        return cnt;
    };
    [&]{
        cir(i,0,n-1){
            cir(i,0,m) if(usiz(i)==nusiz(i)){
                auto u=vector{i},v=vector<int>();
                cir(j,0,m) if(j!=i) v.emplace_back(j);
                if(i==cur) spccase(v,u);
                else spccase(u,v);
                return;
            }
            auto mx=pair(-1,-1);
            cir(i,0,m) if(i!=cur&&(!stcu[i].empty())) mx=max(mx,stcu[i].top());
            assert(mx!=pair(-1,-1));
            ans.emplace_back(mx.second);
            cur=urt[mx.second];
            stcu[cur].pop();
        }
        ans.emplace_back(rt);
    }();
    return ans;
}

