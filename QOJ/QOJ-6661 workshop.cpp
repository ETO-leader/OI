#include"workshop.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

vector<int> a20,a6,a4;

auto initarr(auto&qwq,const int n){
    cir(i,0,(1<<n)){
        const auto cnt=popcount((uint)(i));
        if(cnt==n/2) qwq.emplace_back(i);
    }
}

auto getrank(auto u,auto v,const auto&qwq){
    assert(u!=v);
    u=qwq[u];v=qwq[v];
    auto res=0;
    while((u&1)||(!(v&1))) u>>=1,v>>=1,++res;
    return res;
}

void init(){
    initarr(a20,20);
    initarr(a6,6);
    initarr(a4,4);
}

int morning(int usr,int right){
    return getrank(usr,right,a20);
}

int afternoon(int left,int usr,int right){
    const auto ml=getrank(left,usr,a6);
    const auto mr=getrank(usr,right,a6);
    return getrank(ml,mr,a4);
}

int evening(int left,int usr,int right){
    if(usr<3) return usr;
    auto rest=set{0,1,2};
    for(auto x:{left,right}) rest.extract(x);
    return*rest.begin();
}
