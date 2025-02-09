#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=(int)(998244353);
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
using poly=vector<lint>;
class polybase{
private:
    auto change(poly&a,const auto n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
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
        while((a.size()>1)&&(!a.back())) a.pop_back();
        return a;
    }
} polys;
auto operator*(const poly a,const poly b){
    return polys.mul(a,b);
}
auto operator+(poly a,poly b)->poly{
    if(a.size()<b.size()) return b+a;
    cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
    return a;
}
auto operator-(poly a){
    for(auto&i:a) i=i?MOD-i:0;
    return a;
}
auto fitlen(poly x,const auto n){
    x.resize(n);
    return x;
}
auto inv(poly a,const auto n){
    auto res=poly{math.inv(a[0])};
    a.resize(1<<(int)(ceil(log2(a.size()))));
    for(auto i=1;i<n;i<<=1) res=fitlen(res*fitlen(-(a*res)+poly{2},i<<1),i<<1);
    return fitlen(res,n);
}
auto inv(poly a){return inv(a,a.size());}
auto deriv(poly a){
    const auto n=(int)(a.size());
    auto res=poly(n-1);
    cir(i,1,n) res[i-1]=a[i]*i%MOD;
    return res;
}
auto intge(poly a){
    const auto n=(int)(a.size());
    auto res=poly(n+1);
    cir(i,0,n) res[i+1]=a[i]*math.inv(i+1)%MOD;
    return res;
}
auto ln(poly a){
    return intge(deriv(a)*inv(a));
}
auto exp(poly a){
    auto res=poly{1};
    a.resize(1<<(int)(ceil(log2(a.size()))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=fitlen(res*(poly{1}+(-ln(fitlen(res,i<<1)))+a),i<<1);
    }
    return res;
}
static constexpr auto maxr=(int)(1e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;auto x=poly(maxr);
    cir(i,0,n){
        int w;cin>>w;x[w]=1;
    }
    const auto ansx=x*x;
    auto ans=0ll;
    cir(i,0,maxr) if(x[i]) ans+=ansx[i*2]-1;
    cout<<ans/2<<'\n';
    return 0;
}
