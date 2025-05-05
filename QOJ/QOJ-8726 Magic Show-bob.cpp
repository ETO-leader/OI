#include"Bob.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

static constexpr auto basic_seed=7355608;

long long Bob(vector<pair<int,int>> V){
    mt19937_64 eng(basic_seed);
    static constexpr auto n=4200;
    vector<int> id(n);
    iota(id.begin(),id.end(),0);
    shuffle(id.begin(),id.end(),eng);
    set<pair<int,int>> exist;
    for(auto&[u,v]:V) --u,--v,exist.emplace(u,v),exist.emplace(v,u);
    // unzip seed
    auto _seed=0u;
    cir(i,0,30){
        cir(b,0,10) if(exist.count({id[i*20+b],id[i*20+b+10]})) _seed|=(1<<b);
    }
    // get new rank
    mt19937_64 shuffle_eng(_seed);
    shuffle(id.begin()+600,id.end(),shuffle_eng);
    // receive number
    auto res=0ll;
    cir(i,0,30){
        cir(b,0,60) if(exist.count({id[i*120+b+600],id[i*120+b+660]})) res|=(1ll<<b);
    }
    return res;
}
