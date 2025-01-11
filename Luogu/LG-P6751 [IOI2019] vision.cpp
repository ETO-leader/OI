#include"vision.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using bit=int;

class int10{
private:
    array<int,10> iterator;
public:
    auto&operator[](int x){return iterator[x];}
    auto operator+(bit b){
        auto res=*this;
        cir(i,0,10){
            auto tmp=add_and({b,res[i]});
            res[i]=add_xor({b,res[i]});
            b=tmp;
        }
        return res;
    }
    auto operator==(const int x){
        vector<int> p0,p1;
        cir(i,0,10) ((x>>i)&1?p1:p0).emplace_back(iterator[i]);
        if(p0.empty()) return add_and(p1);
        if(p1.empty()) return add_not(add_or(p0));
        return add_and({add_and(p1),add_not(add_or(p0))});
    }
    int10(const bit OFF){cir(i,0,10) iterator[i]=add_or({OFF});}
};

auto Iota(const int len,int x){
    vector<int> res(len);
    iota(res.begin(),res.end(),x);
    return res;
}

auto write(const bit x){
    add_or({x});
}

void construct_network(int H,int W,int K){
    auto pos=[&](auto x,auto y){
        return x*W+y;
    };
    const auto OFF=add_and(Iota(H*W,0));
    const auto ON=add_or(Iota(H*W,0));
    if(H*W<3){
        if(K==1) add_or({ON});
        else add_or({add_not(ON)});
        return;
    }
    vector<bit> xor_x(H),xor_y(W);
    cir(i,0,H){
        xor_x[i]=add_xor([&]{
            vector<int> res;
            cir(p,0,W) res.emplace_back(pos(i,p));
            return res;
        }());
    }
    cir(i,0,W){
        xor_y[i]=add_xor([&]{
            vector<int> res;
            cir(p,0,H) res.emplace_back(pos(p,i));
            return res;
        }());
    }
    auto prex=xor_x;
    auto prey=xor_y;
    prex[0]=add_or({prex[0]});
    prey[0]=add_or({prey[0]});
    cir(i,1,H) prex[i]=add_xor({prex[i-1],prex[i]});
    cir(i,1,W) prey[i]=add_xor({prey[i-1],prey[i]});
    int10 sum(OFF);
    cir(i,0,H) sum=sum+prex[i];
    cir(i,0,W) sum=sum+prey[i];
    write(sum==K);
}
