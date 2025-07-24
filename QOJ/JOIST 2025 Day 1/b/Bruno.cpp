#include"Bruno.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

int Bruno(int n,int l,vector<int> a){
    static constexpr auto c=11;
    if(l!=(c*4)-2||(!a[0])){
        if(ranges::count(a,1)!=c) return ranges::count(a,1);
        if(a[0]&&ranges::count(a,0)==c) return ranges::count(a,1);
        return n-ranges::count(a,0);
    }
    if([&]{
        cir(i,0,c+1) if(!a[i]) return false;
        return true;
    }()) return ranges::count(a,1);
    auto v0=0,v1=0;
    vector<int> al,ar;
    auto p=0;
    auto c1=0,c0=0;
    for(;al.emplace_back(a[p]),((c1+=a[p])<c);++p);
    for(++p;ar.emplace_back(a[p]),((c0+=(!a[p]))<c);++p);
    for(auto&x:al){
        if(x) v1<<=1;
        else v1|=1;
    }
    for(auto&x:ar){
        if(!x) v0<<=1;
        else v0|=1;
    }
    return max((v0>>1),(v1>>1))+ranges::count(a,1);
}
