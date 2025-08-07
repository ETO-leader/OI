#include"triples.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using lint=long long;

template<const size_t len,const uint k=300>
class ext_bitset{
private:
    bitset<len>*info;
    unordered_set<int> cur;
    auto type(){return info!=nullptr;}
    auto check(){
        if(type()||cur.size()*k<len) return;
        info=new bitset<len>();
        info->reset();
        for(auto&x:cur) info->set(x); 
    }
public:
    static auto count_and(ext_bitset<len,k>&a,ext_bitset<len,k>&b,int delta){
        if(a.type()&&b.type()) return (int)(((*(a.info))&((*(b.info))>>delta)).count());
        if(a.type()){
            auto res=0;
            for(auto&x:b.cur) if(x>delta-1) res+=a.info->test(x-delta);
            return res;
        }else if(b.type()){
            auto res=0;
            for(auto&x:a.cur) if(x+delta<len) res+=b.info->test(x+delta);
            return res;
        }else{
            auto res=0;
            for(auto&x:a.cur) res+=b.cur.contains(x+delta);
            return res;
        }
    }
    auto set(int p){
        if(type()) info->set(p);
        else cur.emplace(p),check();
    }
    ext_bitset():info(nullptr){}
    ~ext_bitset(){if(info) delete info;}
};

static constexpr auto maxn=(int)(2e5+7);

lint count_triples(vector<int> H){
    const auto n=(int)(H.size());
    vector<set<array<int,3>>> vaild(n);
    auto test=[&](int i,int j,int k){
        auto a=array<int,3>({H[i],H[j],H[k]});
        auto b=array<int,3>({abs(i-j),abs(i-k),abs(j-k)});
        ranges::sort(a);
        ranges::sort(b);
        auto p=array<int,3>({i,j,k});
        ranges::sort(p);
        if(a==b) vaild[min({i,j,k})].emplace(p);
    };
    cir(i,0,n){
        if(i-H[i]>-1){
            const auto j=i-H[i];
            if(i-H[j]>-1){
                const auto k=i-H[j];
                test(i,j,k);
            }
            if(i+H[j]<n){
                const auto k=i+H[j];
                test(i,j,k);
            }
            if(j-H[j]>-1){
                const auto k=j-H[j];
                test(i,j,k);
            }
            if(j+H[j]<n){
                const auto k=j+H[j];
                test(i,j,k);
            }
        }
        if(i+H[i]<n){
            const auto j=i+H[i];
            if(i-H[j]>-1){
                const auto k=i-H[j];
                test(i,j,k);
            }
            if(i+H[j]<n){
                const auto k=i+H[j];
                test(i,j,k);
            }
            if(j-H[j]>-1){
                const auto k=j-H[j];
                test(i,j,k);
            }
            if(j+H[j]<n){
                const auto k=j+H[j];
                test(i,j,k);
            }
        }
    }
    auto ans=0ll;
    for(auto&x:vaild) for(auto&[i,j,k]:x){
        ans+=(!(j-i==H[k]&&k-j==H[i]&&k-i==H[j]));
    }
    unordered_map<int,ext_bitset<maxn>> c;
    // H(i) + H(k) = k - i
    // (H(i) + i) = (k - H(k))
    cir(k,0,n){
        ans+=ext_bitset<maxn>::count_and(c[k-H[k]],c[H[k]+k],H[k]);
        c[H[k]+k].set(k);
    }
    return ans;
}

vector<int> construct_range(int M,int K){
    auto type=vector{3,1,2,1,4,3,2,3,1,1,2,3,4,5,4,1,2,1,3,4};
    auto typeii=vector{14,3,4,7,6,1,8,3,2,5,4,13,2,27,10,9,10,7,8,5,6,23,18,17,18,15,12,13,24,15,34,33,8,7,30,29,33,27,5,25,10,3,2,2,20,19,23,4,15,6,27,8,12,10,10,28,13,2,15,4,17,18,7,20,5,10,11,12,9,10,7,8,3,4,5,20,1,2,1,16,11,38,13,8,15,6,9,32,11,10,35,28,33,38,25,4,29,28,21,20,31,24,23,28,27,26,13,12,17,10,15,20,13,18,5,16,25,38,23,8,21,28,3,32,25,6,27,28,3,20,11,10,37,8,15,14,5,18,19,14,15,2,11,12,25,4,27,6,7,30,31,2,33,28,1,14,25,16,27,10,19,20,8,22,15,16,13,18,14,16,1,2,1,9,5,6,6,8,7,6,1,27,3,2,30,15,32,33,34,19,28,9,22,23,24,25,26,15,16,17,18,19,20,3,4,17,9,7,10,9,10,3,6,5,6,7,2,3,4,1,2,1,3,15,16,7,12,5,10,9,8,7,14,7,5,3,7,19,2,7,9,2,9,5,12,12,12,16,15,16,17,5,19,2,3,22,7,24,7,8,9,10,7,8,13,4,15,2,3,2,1,6,5,4,3,6,5,8,7,2,9,4,17,2,15,14,15,10,11,12,9,10,7,8,5,6,3,3,1,2,1,4,8,34,33,5,4,30,37,28,4,26,18,32,12,30,14,15,19,18,10,11,23,22,22,1,16,3,2,3,4,1,2,1,8,11,10,5,8,7,6,4,12,19,18,19,16,15,14,25,24,35,22,21,8,31,26,25,28,27,14,29,38,37,18,35,20,33,6,23,38,37,10,27,12,25,14,31,4,13,6,19,8,37,2,23,4,13,2,3,10,9,10,7,8,5,6,11,8,9,8,19,2,17,22,15,20,21,18,19,10,9,30,13,6,13,26,31,10,29,18,21,20,3,4,23,2,1,20,9,8,11,12,5,14,7,28,11,10,9,2,33,22,5,20,19,18,27,22,29,24,31,26,25,34,27,8,31,30,11,22,13,20,15,2,17,22,3,20,5,5,7,2,9,3,3,12,5,4,9,2,7,18,5,10,3,22,13,4,11,20,9,18,15,6,13,14,3,10,11};
    vector<int> res;
    while((int)(res.size())<M){
        if((int)(res.size())+500>M) for(auto&x:type) res.emplace_back(x);
        else for(auto&x:typeii) res.emplace_back(x);
    }
    return res;
}
