#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    unordered_map<lint,vector<lint>> uwn;
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&x:ifct) x=inv(x);
    }
    constexpr auto fact(const auto x) const{return fct[x];}
    constexpr auto ifact(const auto x) const{return ifct[x];}
    auto wn(const auto h){
        if(uwn.contains(h)) return&uwn[h];
        const auto wx=qpow(omega,(MOD-1)/h);
        vector<lint> xwn(h);
        auto u=1ll;
        for(auto&x:xwn) x=u,(u*=wx)%=MOD;
        uwn[h]=xwn;
        return&uwn[h];
    }
} math;
class poly:public vector<lint>{
public:
    using vector<lint>::vector;
    auto change(poly&a,const auto n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const auto n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            auto wn=math.wn(h);
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*(*wn)[k-i]%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=a[k+midh]>MOD-1?MOD:0;
                    a[k]+=wk;
                    a[k]-=a[k]>MOD-1?MOD:0;
                }
            }
        }
        if(type==-1){
            const auto ivn=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=ivn)%=MOD;
        }
    }
public:
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
    auto transform(const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        resize(nlen);
        ntt<1>(*this,nlen);
    }
    auto itransform(const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        resize(nlen);
        ntt<-1>(*this,nlen);
    }
    auto transform(){transform(size());}
    auto itransform(){itransform(size());}
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
        const auto nlen=1<<(int)(ceil(log2(a.size()+b.size())));
        a.transform(nlen);b.transform(nlen);
        cir(i,0,nlen) (a[i]*=b[i])%=MOD;
        a.itransform();
        return a;
    }
    friend auto inv(poly a,const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        a.resize(nlen);
        auto f=poly{math.inv(a[0])};
        for(auto i=1;i<nlen;i<<=1){
            f=(f*2-(f*f).sized(i<<1)*(a.sized(i<<1))).sized(i<<1);
        }
        return f;
    }
    friend auto operator~(poly a){
        return inv(a,a.size());
    }
    friend auto d_dx(poly a){
        auto res=poly(a.size()-1);
        cir(i,0,(int)(a.size())-1) res[i]=a[i+1]*(i+1)%MOD;
        return res;
    }
    friend auto int_dx(poly a){
        auto res=poly(a.size()+1);
        cir(i,0,(int)(a.size())) res[i+1]=a[i]*math.inv(i+1)%MOD;
        return res;
    }
    friend auto ln(poly a){
        return int_dx(d_dx(a)*(~a));
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    const auto nlen=1<<(int)(ceil(log2(n+1)));
    math.init(nlen+7);
    auto G=poly(nlen);
    G[0]=1;
    cir(i,1,nlen){
        G[i]=((i&1)?MOD-1:1)*math.ifact(i)%MOD*math.qpow(math.inv(2),(lint)(i)*(i-1)/2)%MOD;
    }
    G=~G;
    cir(i,1,nlen){
        (G[i]*=(math.qpow(2,(lint)(i)*(i-1)/2)%MOD))%=MOD;
    }
    G=ln(G);
    cir(i,1,n+1) cout<<G[i]*math.fact(i)%MOD<<'\n';
    return 0;
}
