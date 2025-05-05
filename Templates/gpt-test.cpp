#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
using poly=vector<lint>;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct,ivn;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
    auto init(const int n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ivn=fct;
        ivn[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ivn[i]=ivn[i+1]*(i+1)%MOD;
        ifct=ivn;
        cir(i,1,n) (ivn[i]*=fct[i-1])%=MOD; 
    }
    constexpr auto fact(auto x) const{
        return fct[x];
    }
    constexpr auto ifact(auto x) const{
        return ifct[x];
    }
    constexpr auto pinv(auto x) const{
        return ivn[x];
    }
} math;
class polybase{
private:
    unordered_map<int,vector<int>> chg;
    vector<vector<lint>> omega_k;
    auto change(poly&a,const int n){
        auto&rev=chg[n];
        if(rev.empty()) [[unlikely]]{
            rev.resize(n);
            cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        }
        cir(i,0,n) if(rev[i]<i) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            auto c=__lg(h);
            if(omega_k[c].empty()) [[unlikely]]{
                omega_k[c].resize(midh);
                const auto wx=math.qpow(omega,(MOD-1)/h);
                auto u=1ull;
                cir(i,0,midh) omega_k[c][i]=u,(u*=wx)%=MOD;
            }
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*omega_k[c][k-i]%MOD;
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
    auto mul(poly a,poly b){
        const auto n=1<<(int)(ceil(log2(a.size()+b.size())));
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        return a;
    }
    auto fit_size(auto x,auto siz){
        x.resize(siz);
        return x;
    }
    polybase():omega_k(23){}
} polys;
auto operator+(poly a,poly b){
    a.resize(max(a.size(),b.size()));
    cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
    return a;
}
auto operator-(poly a){
    for(auto&i:a) i=(MOD-i)%MOD;
    return a;
}
auto operator-(poly a,poly b){
    return a+(-b);
}
auto operator*(poly a,poly b){
    return polys.mul(a,b);
}
auto inv(poly a,int req_len){
    a.resize(1<<(int)(ceil(log2(a.size()))));
    const auto n=(int)(a.size());
    poly res{math.inv(a[0])};
    for(auto i=1;i<n;i<<=1){
        res=polys.fit_size(res*polys.fit_size(poly{2}-(polys.fit_size(a,i<<1)*res),i<<1),i<<1);
    }
    res.resize(req_len);
    return res;
}
auto operator~(poly a){
    return inv(a,a.size());
}
auto operator|(poly a,poly b){
    auto c=0;
    while(c<(int)(min(a.size(),b.size())+1)&&(!a[c])&&(!b[c])) ++c;
    a.erase(a.begin(),a.begin()+c);
    b.erase(b.begin(),b.begin()+c);
    return a*(~b);
}
auto int_dx(poly a){
    a.emplace(a.begin(),0);
    cir(i,0,(int)(a.size())) (a[i]*=math.pinv(i))%=MOD;
    return a;
}
auto d_dx(poly a){
    cir(i,0,(int)(a.size())) (a[i]*=i)%=MOD;
    a.erase(a.begin());
    return a;
}
auto ln(poly a){
    return int_dx(d_dx(a)*(~a));
}
auto ln(poly a,auto req_len){
    return int_dx(d_dx(a)*inv(a,req_len));
}
auto exp(poly a){
    auto res=poly{1};
    a.resize(1<<(int)(ceil(log2(a.size()))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=res*polys.fit_size(poly{1}-ln(polys.fit_size(res,i<<1))+a,i<<1);
        res.resize(i<<1);
    }
    return res;
}
auto exp(poly a,auto req_len){
    auto res=poly{1};
    a.resize(req_len);
    a.resize(1<<(int)(ceil(log2(a.size()))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=polys.fit_size(res*polys.fit_size(poly{1}-ln(polys.fit_size(res,i<<1))+a,i<<1),i<<1);
    }
    return res;
}
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
    int k,n;cin>>k>>n;
    math.init(n*4+7);
    auto F=-((poly{1}-x_exp(MOD-k-1,n+7))|(poly{1}-x_exp(MOD-1,n+7)));
    F[0]=0;
    cir(i,1,(int)(F.size())) (F[i]*=math.fact(i-1))%=MOD;
    F.resize(1<<(int)(ceil(log2(n+1))));
    F=exp(F);
    cir(i,1,n+1) cout<<F[i]*math.fact(i)%MOD<<'\n';
    return 0;
}
