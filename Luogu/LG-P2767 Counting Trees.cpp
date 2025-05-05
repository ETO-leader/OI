#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=10007;
template<const int MOD,class fft_type=long double>
class poly:public vector<lint>{
    private:
    using vector<lint>::vector;
    using complf=complex<fft_type>;
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
    auto change(vector<complf>&a,const auto n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
    }
    template<const auto type>
    auto fft(vector<complf>&a,const auto n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complf(
                cosl(numbers::pi_v<fft_type>*2/h),
                sinl(numbers::pi_v<fft_type>*2*type/h)
            );
            for(auto i=0;i<n;i+=h){
                auto u=complf(1,0);
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u;
                    a[k+midh]=a[k]-wk;
                    a[k]+=wk;
                    u*=wx;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
public:
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
        const auto n=1<<(int)(ceil(log2(a.size()+b.size())));
        vector<complf> x(n);
        cir(i,0,(int)(a.size())) x[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) x[i]+=complf(0,b[i]);
        a.fft<1>(x,n);
        for(auto&i:x) i*=i;
        a.fft<-1>(x,n);
        auto res=poly(n);
        cir(i,0,n) res[i]=(lint)(roundl(imag(x[i])/2))%MOD;
        return res;
    }
    friend auto inv(poly a,int req_len){
        a.resize(1<<(int)(ceil(log2(a.size()))));
        const auto n=(int)(a.size());
        poly res{a.math.inv(a[0])};
        for(auto i=1;i<n;i<<=1){
            res=(res*(poly{2}-(a.sized(i<<1)*res)).sized(i<<1)).sized(i<<1);
        }
        res.resize(req_len);
        return res;
    }
    friend auto operator~(poly a){
        return inv(a,a.size());
    }
    friend auto int_dx(poly a){
        a.emplace(a.begin(),0);
        cir(i,0,(int)(a.size())) (a[i]*=a.math.inv(i))%=MOD;
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
    friend auto x_exp(const auto k,auto req_len){
        auto res=poly(req_len);
        res.resize(1<<(int)(ceil(log2(res.size()))));
        auto pwk=1ull;
        cir(i,0,(int)(res.size())){
            res[i]=pwk*res.math.ifact(i)%MOD;
            (pwk*=k)%=MOD;
        }
        return res;
    }
    friend auto pow(poly a,const auto x){
        return exp(ln(a)*x);
    }
    auto shift(){
        auto a=*this;
        a.emplace(a.begin(),0);
        return a;
    }
};
using mpoly=poly<MOD>;
using poly998=poly<998244353>;
using poly107=poly<1000000007>;
using poly109=poly<1000000009>;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    auto newton=[&](const auto n){
        auto f=mpoly{1};
        for(auto i=1;i<n;i<<=1){
            f.resize(i<<1);
            f=(f-(((-pow(f,k).shift())+f-mpoly{1}).sized(i<<1)*(~(((-pow(f,k-1).shift()*k)+mpoly{1}))))).sized(i<<1);
        }
        return f;
    };
    cout<<newton(n+1)[n]<<'\n';
    return 0;
}
