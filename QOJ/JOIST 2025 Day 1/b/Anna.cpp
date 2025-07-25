#include"Anna.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

void Anna(int n){
    static constexpr auto c=11;
    // 11...
    // 00...
    auto c0=0,c1=0;
    auto las=-1;
    auto nxt=[&]{
        return DrawCard(las);
    };
    auto color=[&](int c){
        las=c;
    };
    auto fail=0;
    cir(i,0,n-c*2+2){
        const auto x=nxt();
        if((!x)&&c0<c-1){
            ++c0;
            color(c0+c1-1);
        }else if(x&&c1<c-1){
            ++c1;
            color(0);
        }else{
            color(-1);
            if(x) ++fail;
        }
    }
    if(c0<c-1){
        cir(i,0,c*2-2){
            const auto x=nxt();
            if(!x) color(0);
            else color(-1);
        }
    }else if(c1<c-1){
        cir(i,0,c*2-2){
            const auto x=nxt();
            if(x) color(0);
            else color(-1);
        }
    }else{
        vector<int> p1,p0;
        cir(i,0,c-1) p1.emplace_back(i);
        cir(i,0,c-1) p0.emplace_back(i+c-1);
        vector<int> v1,v0;
        cir(i,0,c-1) if((fail>>(c-i-2))&1) v0.emplace_back(i),v1.emplace_back(i);
        cir(i,0,c*2-2){
            const auto x=nxt();
            if((!x)&&(!v1.empty())){
                const auto p=v1.back();v1.pop_back();
                if(p) color(p1[p-1]+1);
                else color(0);
                cir(x,p,c-1) ++p1[x];
                for(auto&x:p0) ++x;
            }else if(!x){
                color(c*2-2+i);
            }else if(x&&(!v0.empty())){
                const auto p=v0.back();v0.pop_back();
                if(p) color(p0[p-1]+1);
                else color(p1[c-2]+1);
                cir(x,p,c-1) ++p0[x];
            }else{
                color(c*2-2+i);
            }
        }
    }
    nxt();
}
