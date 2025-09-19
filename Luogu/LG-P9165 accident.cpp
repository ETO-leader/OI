#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
class poly:public vector<lint>{
public:
    using vector<lint>::vector;
    auto sized(const auto n){
        auto res=*this;
        res.resize(n);
        return res;
    }
    auto shrink(){
        auto a=*this;
        while(a.size()>1&&(!a.back())) a.pop_back();
        return a;
    }
    auto shift(){
        auto a=*this;
        a.emplace(a.begin(),0);
        return a;
    }
    friend auto operator+(poly a,poly b){
        a.resize(max(a.size(),b.size()));
        cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
        return a;
    }
    friend auto operator-(poly a){
        for(auto&i:a) (i=MOD-i)%=MOD;
        return a;
    }
    friend auto operator-(poly a,poly b){
        return a+(-b);
    }
    friend auto operator*(poly a,auto b) requires is_integral_v<decltype(b)>{
        for(auto&i:a) (i*=b)%=MOD;
        return a;
    }
    friend auto operator*(poly a,poly b){
        auto res=poly(a.size()+b.size()-1);
        cir(i,0,(int)(a.size())) cir(j,0,(int)(b.size())){
            (res[i+j]+=a[i]*b[j])%=MOD;
        }
        return res;
    }
    friend auto operator/(poly f,auto x){
        const auto[b,a]=x;
        const auto iv=math.inv(a);
        auto res=poly(f.size());
        for(auto i=(int)(f.size())-1;i;--i){
            const auto k=f[i]*iv%MOD;
            res[i-1]=k;
            f[i]+=MOD-a*k%MOD;
            f[i-1]+=MOD-b*k%MOD;
        }
        return res;
    }
    auto f(const auto x){
        auto res=0ll,pw=1ll;
        for(auto&i:*this) (res+=i*pw)%=MOD,(pw*=x)%=MOD;
        return res;
    }
};
auto getvalues(poly a,const vector<lint> p){
    vector<lint> res(p.size());
    cir(i,0,(int)(p.size())) res[i]=a.f(p[i]);
    return res;
}
auto lagrange(const vector<lint> a,const vector<lint> b){
    const auto n=(int)(a.size());
    auto ans=poly(),f=poly({1});
    cir(i,0,n) f=f*poly({-a[i],1});
    cir(i,0,n){
        const auto c=[&]{
            lint x=1;
            cir(j,0,n) if(i!=j){
                (x*=(a[i]+MOD-a[j])%MOD)%=MOD;
            }
            return math.inv(x);
        }()*b[i]%MOD;
        ans=ans+(f/pair(-a[i],1))*c;
    }
    return ans;
}

vector<int> Encode(vector<int> a){
    vector<lint> pos(150);
    ranges::iota(pos,0);
    const auto val=getvalues(poly(a.begin(),a.end()),pos);
    vector<int> res;
    for(auto&x:val) cir(i,0,5) res.emplace_back(x);
    return res;
}

vector<int> Decode(vector<int> a){
    vector<lint> val,pos;
    cir(i,0,150){
        map<int,int> cnt;
        cir(p,i*5,i*5+5) ++cnt[a[p]];
        map<int,int> xcnt;
        for(auto&[a,b]:cnt) ++xcnt[b];
        if(xcnt.rbegin()->second>1) continue;
        for(auto&[a,b]:cnt) if(b==xcnt.rbegin()->first){
            val.emplace_back(a);
            pos.emplace_back(i);
        }
    }
    while(val.size()>102) val.pop_back(),pos.pop_back();
    auto res=lagrange(pos,val);
    while(res.size()>100) res.pop_back();
    return vector<int>(res.begin(),res.end());
}
