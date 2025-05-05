#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
using poly=vector<lint>;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<uint> fct,ifct,ivn;
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
        cir(i,1,n) fct[i]=1ull*fct[i-1]*i%MOD;
        ivn=fct;
        ivn[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ivn[i]=1ull*ivn[i+1]*(i+1)%MOD;
        ifct=ivn;
        cir(i,1,n) ivn[i]=(1ull*ivn[i]*fct[i-1])%MOD; 
    }
    constexpr auto fact(auto x) const->lint{
        return fct[x];
    }
    constexpr auto ifact(auto x) const->lint{
        return ifct[x];
    }
    constexpr auto pinv(auto x) const->lint{
        return ivn[x];
    }
    constexpr auto C(auto a,auto b) const{
        return 1ull*fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
class polybase{
private:
    auto change(poly&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(rev[i]<i) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ull;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=a[k+midh]>MOD-1?MOD:0;
                    a[k]+=wk;
                    a[k]-=a[k]>MOD-1?MOD:0;
                    (u*=wx)%=MOD;
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
auto inv(poly a,auto req_len){
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
    int n,m;cin>>n>>m;vector<int> a(n);
    for(auto&i:a) cin>>i;
    const auto nlen=1<<(int)(ceil(log2(n+m+1)));
    math.init(nlen*2+m+7);
    vector<int> c(n);
    for(auto&x:a) ++c[x];
    auto sum=0ull;
    cir(i,1,n) sum+=(lint)(c[i])*(c[i]-1)/2;
    auto G=poly(nlen);
    map<int,int> cnt;
    cir(i,1,n) cnt[c[i-1]]+=c[i];
    for(auto&[w,x]:cnt) if(w){
        for(auto i=1;i*w<nlen;++i) (G[i*w]+=x*math.inv(i)%MOD)%=MOD;
    }
    G=~exp(G);
    if((n-1)&1) G=-G;
    auto H=poly(nlen);
    const auto ad=nlen-1;
    cir(i,0,nlen) H[ad-i]=math.ifact(i);
    cir(i,0,nlen) (G[i]*=math.fact(i))%=MOD;
    auto F=G*H;
    F=poly(F.begin()+ad,F.end());
    cir(i,0,nlen) (F[i]*=math.ifact(i))%=MOD;
    auto ans=0ull;
    auto curdwn=1ull;
    cir(i,0,m+1){
        if(i) (curdwn*=(sum-i+1))%=MOD;
        if(m-i<(int)(F.size())) (ans+=curdwn*math.ifact(i)%MOD*F[m-i])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
