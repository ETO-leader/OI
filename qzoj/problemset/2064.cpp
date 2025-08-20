#pragma GCC target("popcnt")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dynamic_bitset{
private:
    vector<uint64_t> a;
    static constexpr auto full=numeric_limits<uint64_t>::max();
public:
    auto set(int p){
        a[p>>6]|=((uint64_t)(1)<<(p&63));
    }
    auto flip(int p){
        a[p>>6]^=((uint64_t)(1)<<(p&63));
    }
    auto reset(int p){
        set(p);flip(p);
    }
    auto at(int p){
        return (a[p>>6]>>(p&63))&1;
    }
    auto&operator&=(dynamic_bitset x){
        assert(a.size()==x.a.size());
        cir(i,0,(int)(a.size())) a[i]&=x.a[i];
        return*this;
    }
    auto operator&(dynamic_bitset x) const{
        auto res=*this;
        return res&=x;
    }
    auto&operator|=(dynamic_bitset x){
        assert(a.size()==x.a.size());
        cir(i,0,(int)(a.size())) a[i]|=x.a[i];
        return*this;
    }
    auto operator|(dynamic_bitset x) const{
        auto res=*this;
        return res|=x;
    }
    auto&operator^=(dynamic_bitset x){
        assert(a.size()==x.a.size());
        cir(i,0,(int)(a.size())) a[i]^=x.a[i];
        return*this;
    }
    auto operator^(dynamic_bitset x) const{
        auto res=*this;
        return res|=x;
    }
    auto count(int l,int r) const{
        const auto fb=l>>6,lb=r>>6,lc=l&63,hc=r&63;
        auto res=0;
        if(fb==lb){
            auto mask=(full<<lc)&(full>>(63-hc));
            res+=__builtin_popcountll(a[fb]&mask);
            return res;
        }
        const auto maskf=full<<lc;
        res+=__builtin_popcountll(a[fb]&maskf);
        cir(i,fb+1,lb) res+=__builtin_popcountll(a[i]);
        const auto maskl=full>>(63-hc);
        res+=__builtin_popcountll(a[lb]&maskl);
        return res;
    }
    dynamic_bitset(auto _n):a((_n>>6)+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<string> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<int>> rg(n,vector<int>(m)),dw(n,vector<int>(m));
    cir(i,0,n) cir(j,0,m-1) rg[i][j]=(a[i][j]!=a[i][j+1]);
    cir(i,0,n-1) cir(j,0,m) dw[i][j]=(a[i][j]!=a[i+1][j]);
    vector<dynamic_bitset> vrg(n,dynamic_bitset(m)),vdw(n,dynamic_bitset(m));
    cir(r,0,n){
        auto suf=0;
        for(auto i=m-1;~i;--i) if(suf^=rg[r][i]) vrg[r].set(i);
        suf=0;
        for(auto i=m-1;~i;--i) if(suf^=dw[r][i]) vdw[r].set(i);
    }
    auto ans=0ll;
    cir(l,0,n){
        dynamic_bitset udw(m),urg(m);
        cir(r,l,n){
            vector<int> cnt(2);
            urg^=vrg[r];
            const auto vx=urg^udw;
            cir(i,0,m){
                ++cnt[urg.at(i)^udw.at(i)];
                const auto xw=urg.at(i)^(i+1<m?udw.at(i+1):0);
                ans+=cnt[xw^1];
            }
            udw^=vdw[r];
        }
    }
    cout<<ans<<'\n';
    return 0;
}

