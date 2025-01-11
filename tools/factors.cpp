#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=__int128_t;
constexpr auto arrs={2,3,5,7,11,13,17,19,23,29,31,37,43,47,53,59,61,67,71,73};
random_device rnd;
template<typename _Ty>
constexpr auto qpow(_Ty a,lint b,const _Ty mod){
    auto res=(_Ty)(1);
    while(b){
        if(b&1) (res*=a)%=mod;
        (a*=a)%=mod;b>>=1;
    }
    return res;
}
auto operator""ql(unsigned long long x){
    return __int128_t(x);
}
constexpr auto miller_rabin(lint x){
    if(!(x&1)) return x==2;
    auto u=x-1,t=1ql;
    while(!(u&1)) (u>>=1),++t;
    for(const auto a:arrs) if(a<x){
        auto w=qpow<__int128_t>(a,u,x);
        if(w==1) continue;
        auto s=0;
        for(;s<t;++s){
            if(w==x-1) break;
            (w*=w)%=x;
        }
        if(s==t) return false;
    }
    return true;
}
auto rndlong(auto mod){
    return 1ql*rnd()*rnd()%mod*rnd()%mod*rnd()%mod;
}
constexpr auto abs(lint x){
    return x<0?-x:x;
}
constexpr auto gcd(lint a,lint b){
    if(!b) return a;
    return gcd(b,a%b);
}
auto __pollard_rho(lint x){
    auto s=0ql,t=0ql;
    const auto w=rndlong(x-1)+1;
    auto stp=0,cnt=0;
    for(auto gl=1ql,val=1ql;(++cnt)<64;gl*=2,s=t,val=1){
        for(stp=0;stp<gl+1;++stp){
            t=((__int128_t)(t)*t+w)%x;
            val=(__int128_t)(val)*abs(t-s)%x;
            if(!(stp%127)){
                const auto d=gcd(val,x);
                if(d>1) return d;
            }
        }
        const auto d=gcd(val,x);
        if(d>1) return d;
    }
    return -1ql;
}
auto pollard_rho(lint x){
    auto w=-1ql;
    for(;w==-1ql;w=__pollard_rho(x));
    return w;
}
auto check(lint x,multiset<lint>&a){
    if(x<2) return;
    if(miller_rabin(x)) return a.insert(x),void();
    auto p=x;
    while(p>x-1) p=pollard_rho(x);
    check(p,a);check(x/p,a);
}
ostream&operator<<(ostream&os,lint x){
    if(x>9) os<<(x/10);
    return os<<(int)(x%10);
}
int main(int argc,char*argv[]){
    ios::sync_with_stdio(false),cin.tie(0);
    auto T=1;
    while(T--){
        auto x=0ql;
        for(auto w:string_view(argv[1])) (x*=10)+=w-'0';
        multiset<lint> ans;
        check(x,ans);
        for(auto&i:ans) print("{} ",i);
        println("");
    }
    return 0;
}
