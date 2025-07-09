#include <map>
#include <random>
#include <numbers>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <ranges>
#include <algorithm>
#include <sstream>
#include "incursion.h"

#ifdef __HIDE_LOGS

std::stringstream ____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________cerr;
#define cerr ____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________cerr

#endif

using namespace std;

vector<int> __IdA,__IdB,__STATE;

int cur;

set<pair<int,int>> ues;

int cnt;

int visit(int u){
    ++cnt;
    cerr<<"move: "<<cur<<" -> "<<u<<' '<<'('<<__IdB[cur-1]<<" --> "<<__IdB[u-1]<<')'<<'\n';
    if(!ues.contains({__IdB[cur-1],__IdB[u-1]})) cerr<<"Invaild movement.\n",exit(3);
    cur=u;
    return __STATE[__IdB[u-1]-1];
}

int main(){
    int _seed;cin>>_seed;
    int n;cin>>n;
    vector<pair<int,int>> es(n-1);
    for(auto&[u,v]:es) cin>>u>>v;
    __IdA.resize(n);
    __IdB.resize(n);
    ranges::iota(__IdA,1);
    ranges::iota(__IdB,1);
    mt19937 eng(_seed);
    ranges::shuffle(__IdA,eng);
    ranges::shuffle(__IdB,eng);
    for(auto&[u,v]:es) ues.emplace(u,v),ues.emplace(v,u);
    vector<pair<int,int>> esA,esB;
    map<int,int> raId,rbId;
    for(int i=0;i<n;++i) raId[__IdA[i]]=i;
    for(int i=0;i<n;++i) rbId[__IdB[i]]=i;
    for(auto&[u,v]:es) esA.emplace_back(raId[u]+1,raId[v]+1);
    for(auto&[u,v]:es) esB.emplace_back(rbId[u]+1,rbId[v]+1);
    ranges::shuffle(esA,eng);
    ranges::shuffle(esB,eng);
    int u,v;cin>>u>>v;
    cur=rbId[v]+1;
    const auto uSTATE=mark(esA,raId[u]+1);
    __STATE.resize(n);
    for(int i=0;i<n;++i) __STATE[__IdA[i]-1]=uSTATE[i];
    for(auto&i:__STATE) cerr<<i<<' ';
    cerr<<'\n';
    locate(esB,rbId[v]+1,__STATE[v-1]);
    if(__IdB[cur-1]==u) cout<<"ok: "<<cnt<<'\n';
    else cout<<"wa "<<u<<' '<<__IdB[cur-1]<<'\n';
    return 0;
}
