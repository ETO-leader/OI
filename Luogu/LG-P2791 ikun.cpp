#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
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
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct.resize(n);
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    constexpr auto fact(auto x) const{return fct[x];}
    constexpr auto ifact(auto x) const{return ifct[x];}
    constexpr auto C(auto a,auto b) const{
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
class poly:public vector<lint>{
private:
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
            const auto wx=math.qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ll;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    (a[k+midh]=a[k]+MOD-wk)%=MOD;
                    (a[k]+=wk)%=MOD;
                    (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            reverse(a.begin()+1,a.end());
            const auto ivn=math.inv(n);
            for(auto&i:a) (i*=ivn)%=MOD;
        }
    }
    auto verify_size(poly&a){
        const auto nsiz=1<<(int)(ceil(log2(a.size())));
        a.resize(nsiz);
    }
public:
    auto transform(const auto n){
        this->resize(n);
        verify_size(*this);
        ntt<1>(*this,(int)(this->size()));
    }
    auto itransform(const auto n){
        this->resize(n);
        verify_size(*this);
        ntt<-1>(*this,(int)(this->size()));
    }
    auto transform(){transform(this->size());}
    auto itransform(){itransform(this->size());}
    auto sized(const auto n){
        auto a=*this;a.resize(n);
        return a;
    }
    friend auto operator+(poly a,poly b){
        a.resize(max(a.size(),b.size()));
        cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
        return a;
    }
    friend auto operator-(poly a){
        for(auto&i:a) i=(MOD-i)%MOD;
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
        const auto nlen=1<<(int)(ceil(log2(a.size()+b.size()-1)));
        a.transform(nlen);b.transform(nlen);
        cir(i,0,nlen) (a[i]*=b[i])%=MOD;
        a.itransform();
        return a;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,s,l;cin>>n>>m>>s>>l;math.init(max(n,l)+7);
    auto f=poly(l+1),g=poly(l+1);
    cir(i,0,l+1) f[i]=math.qpow(i,l)*math.ifact(i)%MOD;
    cir(i,0,l+1) g[i]=((i&1)?MOD-1:1)*math.ifact(i)%MOD;
    const auto S=(f*g).sized(l+1);
    cir(c,0,s){
        int un,um,k;cin>>un>>um>>k;
        auto ans=0ll;
        cir(i,0,l+1) (ans+=S[i]*math.fact(i)%MOD*math.C(um,i)%MOD*math.C(un-i,k-i))%=MOD;
        cout<<(ans*math.inv(math.C(un,k)))%MOD<<'\n';
    }
    return 0;
}
