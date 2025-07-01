#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty,const size_t len> requires is_unsigned_v<_Ty>
class static_bitset{
private:
    static constexpr auto ulen=numeric_limits<_Ty>::digits;
    array<_Ty,len/ulen+7> a;
public:
    auto set(int p){
        a[p/ulen]|=((_Ty)(1)<<(p%ulen));
    }
    auto count(const auto k) const{
        auto res=0;
        cir(i,0,k/ulen) res+=popcount(a[i]);
        if(k%ulen) res+=popcount(a[k/ulen]<<(ulen-k%ulen));
        return res;
    }
    auto operator<<=(const auto k){
        const auto bl=k/ulen,v=k%ulen;
        auto p=(int)(a.size()-1);
        for(auto i=(int)(a.size())-1;~i;--i){
            p=i;
            a[i]=(a[i-bl]<<v);
            if(i-bl-1<0) break;
            a[i]|=(a[i-bl-1]>>(ulen-v));
        }
        cir(x,0,p) a[p]=0;
    }
    auto operator&=(const static_bitset<_Ty,len> x){
        cir(i,0,(int)(a.size())) a[i]&=x.a[i];
    }
    auto operator|=(const static_bitset<_Ty,len> x){
        cir(i,0,(int)(a.size())) a[i]|=x.a[i];
    }
    auto rshift_nand(const static_bitset<_Ty,len> x,int k){
        auto u=k/ulen,v=k%ulen;
        cir(i,0,(int)(a.size())){
            if(i+u>(int)(a.size())-2) break;
            auto nw=(x.a[i+u]>>v);
            if(v) nw|=(x.a[i+u+1]<<(64-v));
            a[i]&=~nw;
        }
    }
    auto rshift_or(const static_bitset<_Ty,len> x,int k){
        auto u=k/ulen,v=k%ulen;
        cir(i,0,(int)(a.size())){
            if(i+u>(int)(a.size())-2) break;
            auto nw=(x.a[i+u]>>v);
            if(v) nw|=(x.a[i+u+1]<<(64-v));
            a[i]|=nw;
        }
    }
    static_bitset(){
        memset(a.begin(),0,sizeof(a));
    }
};
static constexpr auto maxb=50007;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,T;cin>>c>>T;
    while(T--) []{
        int n,m;string s;cin>>n>>m>>s;
        vector<vector<pair<int,int>>> q(n);
        cir(i,0,m){
            int p,r;cin>>p>>r;--p;
            q[p].emplace_back(r,i);
        }
        vector<vector<static_bitset<uint64_t,maxb>>> a(2,vector<static_bitset<uint64_t,maxb>>(26));
        vector<vector<static_bitset<uint64_t,maxb>>> b(2,vector<static_bitset<uint64_t,maxb>>(26));
        vector<int> c{50000,50000};
        static_bitset<uint64_t,maxb> f;
        vector<int> ans(m);
        for(auto i=n-2;~i;--i){
            const auto op=(i&1),uc=s[i+1]-'a';
            f<<=1;--c[op];
            cir(x,0,uc) a[op][x].set(c[op]);
            cir(x,uc+1,26) b[op][x].set(c[op]);
            const auto vc=s[i]-'a';
            if(vc) f.rshift_nand(b[op][vc],c[op]);
            if(vc+1<26) f.rshift_or(a[op][vc],c[op]);
            for(auto&[r,id]:q[i]) ans[id]=f.count(r);
        }
        for(auto&i:ans) cout<<i<<'\n';
    }();
    return 0;
}


