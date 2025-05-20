#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
    unordered_map<lint,vector<lint>> uwn;
    unordered_map<lint,vector<int>> urev;
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
    auto wn(const auto h){
        if(uwn.count(h)) return&uwn[h];
        const auto wx=qpow(omega,(MOD-1)/h);
        vector<lint> xwn(h);
        auto u=1ll;
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
        cir(i,0,(int)(a.size())) (a[i]*=math.inv(i))%=MOD;
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
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;++n;++m;
    const auto nlen=1<<(int)(ceil(log2(max(n,m)+1)));
    poly f(n),g(m);
    for(auto&i:f) cin>>i;
    for(auto&i:g) cin>>i;
    f.resize(nlen);
    g.resize(nlen);
    const auto sqr=(int)(sqrt(nlen)+3);
    vector<poly> pw(sqr);
    auto p=poly{1}.sized(nlen);
    cir(i,0,sqr){
        pw[i]=p;
        p=(p*g).sized(nlen);
    }
    auto q=poly{1}.sized(nlen);
    auto h=poly(nlen);
    cir(i,0,sqr){
        auto sum=poly(nlen);
        cir(j,0,sqr){
            const auto len=i*sqr+j;
            if(len>nlen-1) continue;
            cir(i,0,nlen) (sum[i]+=pw[j][i]*f[len])%=MOD;
        }
        h=h+(q*sum).sized(nlen);
        q=(q*p).sized(nlen);
    }
    h.resize(n);
    for(auto&i:h) cout<<i<<' ';
    cout<<'\n';
    return 0;
}