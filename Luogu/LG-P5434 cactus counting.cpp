#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
    unordered_map<lint,vector<lint>> uwn;
    unordered_map<lint,vector<int>> urev;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto wn(const auto h){
        if(uwn.count(h)) return&uwn[h];
        const auto wx=qpow(omega,(MOD-1)/h);
        vector<lint> xwn(h);
        auto u=1ull;
        for(auto&x:xwn) x=u,(u*=wx)%=MOD;
        uwn[h]=xwn;
        return&uwn[h];
    }
    auto rev(const auto h){
        if(urev.count(h)) return&urev[h];
        vector<int> xrev(h);
        cir(i,0,h) xrev[i]=(xrev[i>>1]>>1)|((h>>1)*(i&1));
        urev[h]=xrev;
        return&urev[h];
    }
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct.resize(n);
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    constexpr auto fact(const auto x) const{return fct[x];}
    constexpr auto ifact(const auto x) const{return ifct[x];}
    constexpr auto pinv(const auto x) const{return ifct[x]*(x?fct[x-1]:0)%MOD;}
} math;
class poly:public vector<lint>{
public:
    using vector<lint>::vector;
    auto change(poly&a,const auto n){
        auto rev=math.rev(n);
        cir(i,0,n) if(i<(*rev)[i]) std::swap(a[i],a[(*rev)[i]]);
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
                    a[k+midh]=a[k]+MOD-wk>MOD-1?a[k]-wk:a[k]+MOD-wk;
                    a[k]=a[k]+wk>MOD-1?a[k]+wk-MOD:a[k]+wk;
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
    auto shift(){
        auto a=*this;
        a.emplace(a.begin(),0);
        return a;
    }
    auto ishift(){
        auto a=*this;
        a.erase(a.begin());
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
    friend auto operator*(poly a,auto b){
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
    friend auto int_dx(poly a){
        a.emplace(a.begin(),0);
        cir(i,0,(int)(a.size())) (a[i]*=math.pinv(i))%=MOD;
        return a;
    }
    friend auto d_dx(poly a){
        cir(i,0,(int)(a.size())) (a[i]*=i)%=MOD;
        a.erase(a.begin());
        return a;
    }
    friend auto ln(poly a,auto req_len){
        return int_dx(d_dx(a)*inv(a,req_len));
    }
    friend auto ln(poly a){
        return ln(a,a.size());
    }
    friend auto exp(poly a,auto req_len){
        auto res=poly{1};
        a.resize(req_len);
        a.resize(1<<(int)(ceil(log2(a.size()))));
        const auto n=(int)(a.size());
        for(auto i=1;i<n;i<<=1){
            res=(res*(poly{1}-ln(res.sized(i<<1))+a).sized(i<<1)).sized(i<<1);
        }
        return res;
    }
    friend auto exp(poly a){
        return exp(a,a.size());
    }
    friend auto pow(poly a,const auto x){
        return exp(ln(a)*x);
    }
    friend auto dot(poly a,poly b){
        assert(a.size()==b.size());
        cir(i,0,(int)(a.size())) (a[i]*=b[i])%=MOD;
        return a;
    }
    friend auto operator/(poly a,poly b){
        const auto n=(int)(a.size()),m=(int)(b.size());
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
        a.resize(max(n-m+1,1));
        b.resize(max(n-m+1,1));
        auto q=a*(~b);
        q.resize(max(n-m+1,1));
        reverse(q.begin(),q.end());
        return q;
    }
    friend auto operator%(poly a,poly b){
        return a-b*(a/b);
    }
    friend auto square(poly a){
        const auto nlen=1<<(int)(ceil(log2(a.size())));
        a.transform(nlen*2);
        a=dot(a,a);
        a.itransform();
        return a;
    }
};
auto x_exp(const auto k,auto req_len){
    auto res=poly(req_len);
    res.resize(1<<(int)(ceil(log2(res.size()))));
    auto pwk=1ull;
    cir(i,0,(int)(res.size())){
        res[i]=pwk*math.ifact(i)%MOD;
        (pwk*=k)%=MOD;
    }
    return res;
}
class ebcc{
public:
    static auto count(const int n){
        const auto nlen=1<<(int)(ceil(log2(n+1)));
        auto g=poly(nlen);
        cir(i,0,nlen) g[i]=math.qpow(2,(lint)(i)*(i-1)/2)*math.ifact(i)%MOD;
        g=ln(g).sized(nlen);
        cir(i,0,nlen) (g[i]*=(MOD-i))%=MOD;
        g=exp(g*n)*math.inv((MOD-(lint)(n)*n%MOD)%MOD);
        return g[n]*math.fact(n)%MOD;
    }
};
class vbcc{
public:
    static auto count(const int n){
        if(n<3) return 1ull;
        const auto nlen=1<<(int)(ceil(log2(n+3)));
        auto f=poly(nlen);
        cir(i,0,nlen) f[i]=math.qpow(2,(lint)(i)*(i-1)/2)*math.ifact(i)%MOD;
        f=ln(f).sized(nlen);
        cir(i,0,nlen) (f[i]*=i)%=MOD;
        const auto h=ln((f.ishift()).sized(nlen)).sized(nlen);
        const auto uh=d_dx(h).sized(nlen);
        const auto eh=exp(h*((MOD-n+1)%MOD)).sized(nlen);
        const auto g=(uh*eh).sized(nlen);
        return g[n-2]*math.fact(n-2)%MOD;
    }
};
class cactus{
public:
    static auto count(const auto n){
        const auto nlen=1<<(int)(ceil(log2(n+1)));
        auto f=poly{0};
        for(auto i=1;i<n;i<<=1){
            auto h=((-((f*f).sized(i<<1))+f*2)*(~(poly{2}-f.sized(i<<1)*2))).sized(i<<1);
            h=exp(h).shift().sized(i<<1);
            const auto g=(poly{1}+(~(square(f-poly{1})))).sized(i<<1);
            f=(f-(h*2-f*2)*((~((h*g).sized(i<<1)-poly{2})).sized(i<<1))).sized(i<<1);
        }
        cir(i,0,nlen) (f[i]*=math.inv(i))%=MOD;
        f=exp(f);
        return f[n]*math.fact(n)%MOD;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    const auto nlen=1<<(int)(ceil(log2(n+1)));
    math.init(nlen*2+7);
    cout<<cactus::count(n)<<'\n';
    return 0;
}
