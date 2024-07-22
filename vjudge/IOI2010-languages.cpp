#include"lang.h"
#include"grader.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using ulint=unsigned long long;

map<vector<int>,unordered_set<int>> crsap;

void excerpt(int*a){
    const auto len=100;
    unordered_map<int,int> prob;
    cir(i,0,len){
        for(auto&x:crsap[{a[i]}]) prob[x]+=6;
    }
    cir(i,0,len-2){
        for(auto&x:crsap[{a[i],a[i+1],a[i+2]}]) prob[x]+=5;
    }
    cir(i,0,len-4){
        for(auto&x:crsap[{a[i],a[i+1],a[i+2],a[i+3],a[i+4]}]) prob[x]+=10;
    }
    pair<int,int> hx={-1,-1};
    for(auto&[ax,bx]:prob) hx=max(hx,{bx,-ax});
    const auto ql=language(-hx.second);
    cir(i,0,len){
        crsap[{a[i]}].insert(ql);
    }
    cir(i,0,len-2){
        crsap[{a[i],a[i+1],a[i+2]}].insert(ql);
    }
    cir(i,0,len-4){
        crsap[{a[i],a[i+1],a[i+2],a[i+3],a[i+4]}].insert(ql);
    }
}
