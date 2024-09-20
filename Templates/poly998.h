#include<vector>
#include<random>
#include<algorithm>
#include<cmath>
#include<complex>

#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using poly=std::vector<lint>;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
std::mt19937_64 eng(
    std::random_device().operator()()
);
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
    constexpr auto omegak(int k){
        return qpow(omega,(MOD-1)/k);
    }
} math;
class polybase{
private:
    auto change(poly&a,const int n){
        std::vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(rev[i]<i) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=math.omegak(h);
            for(auto i=0;i<n;i+=h){
                auto u=1ll;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    a[k+midh]=(a[k]+MOD-wk)%MOD;
                    (a[k]+=wk)%=MOD;
                    (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            const auto ivn=math.inv(n);
            std::reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=ivn)%=MOD;
        }
    }
public:
    auto rsiz(poly x,const int len){
        return x.resize(len),x;
    }
    auto removez(poly x){
        while((x.size()>1)&&(!(x.back()%MOD))) x.pop_back();
        return x;
    }
    auto mul(poly&a,poly&b){
        const auto n=1<<(int)(std::log2(a.size()+b.size())+1);
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        return a;
    }
} polys;
auto operator+(poly a,poly b)->poly{
    if(a.size()<b.size()) return b+a;
    cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
    return polys.removez(a);
}
auto operator-(poly a){
    for(auto&i:a) if(i) i=MOD-i;
    return a;
}
auto operator-(poly a,poly b){
    return a+(-b);
}
auto operator*(poly a,poly b){
    return polys.removez(polys.mul(a,b));
}
auto inv(poly a,const int len){
    auto res=poly{math.inv(a[0])};
    a.resize(1<<(int)(std::ceil(std::log2(len))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=polys.rsiz(res*polys.rsiz(polys.rsiz(-a,i<<1)*res+poly{2},i<<1),i<<1);
    }
    return polys.rsiz(res,len);
}
auto inv(poly a){
    return inv(a,a.size());
}
auto operator/(poly a,poly b){
    const auto n=(int)(a.size()),m=(int)(b.size());
    std::reverse(a.begin(),a.end());
    std::reverse(b.begin(),b.end());
    a.resize(std::max(n-m+1,1));
    b.resize(std::max(n-m+1,1));
    auto q=a*inv(b);
    q.resize(std::max(n-m+1,1));
    std::reverse(q.begin(),q.end());
    return q;
}
auto operator%(poly a,poly b){
    return a-b*(a/b);
}
auto intp(poly a){
    const auto n=(int)(a.size());
    auto res=poly(n+1);
    cir(i,0,n){
        res[i+1]=a[i]*math.inv(i+1)%MOD;
    }
    return res;
}
auto dx(poly a){
    const auto n=(int)(a.size());
    auto res=poly(n-1);
    cir(i,1,n) res[i-1]=i*a[i]%MOD;
    return res;
}
auto ln(poly a){
    return intp(dx(a)*inv(a));
}
auto exp(poly a){
    auto res=poly{1};
    a.resize(1<<(int)(std::ceil(std::log2(a.size()))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=polys.rsiz(res*(poly{1}-ln(polys.rsiz(res,i<<1))+polys.rsiz(a,i<<1)),i<<1);
    }
    return res;
}
class cipolla{
private:
    using compli=std::complex<lint>;
    lint w;
    auto mul(compli a,compli b){
        return compli(
            (std::real(a)*std::real(b)+std::imag(a)*std::imag(b)%MOD*w)%MOD,
            (std::imag(a)*std::real(b)+std::imag(b)*std::real(a))%MOD
        );
    }
    auto qpow(compli a,lint b){
        auto res=compli(1,0);
        while(b){
            if(b&1) res=mul(res,a);
            a=mul(a,a);b>>=1;
        }
        return res;
    }
    auto fnd(const lint n){
        std::uniform_int_distribution<lint> rnd(0,MOD-1);
        while(true){
            const auto x=rnd(eng);
            if(math.qpow((w=(x*x+MOD-n)%MOD),(MOD-1)/2)==MOD-1) return x;
        }
        abort();
    }
public:
    auto solve(const lint n){
        return std::real(qpow(compli(fnd(n),1),(MOD+1)/2));
    }
};
auto sqrt(poly a){
    auto res=poly{cipolla().solve(a[0])};
    res[0]=min(res[0],MOD-res[0]);
    a.resize(1<<(int)(std::ceil(std::log2(a.size()))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=polys.rsiz((res*res+polys.rsiz(a,i<<1))*inv(res*poly{2},i<<1),i<<1);
    }
    return res;
}
auto pow(poly a,lint b,const int n){
    a.resize(n);
    auto res=poly{1};
    while(b){
        if(b&1) (res=res*a).resize(n);
        (a=a*a).resize(n);b>>=1;
    }
    return res;
}
