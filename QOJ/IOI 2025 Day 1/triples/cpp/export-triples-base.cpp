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

extern "C"{
    long long count(const int*data,size_t len){
        vector<int> v(data,data+len);
        return count_triples(v);
    }
}
