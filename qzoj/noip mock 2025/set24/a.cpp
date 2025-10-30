#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
template<const int maxn>
class bigint:public array<int16_t,maxn>{
public:
    friend auto operator+(bigint<maxn> a,bigint<maxn> b){
        auto w=0;
        cir(i,0,maxn){
            a[i]+=b[i]+w;
            w=a[i]/10;
            a[i]%=10;
        }
        return a;
    }
    friend auto operator*(bigint<maxn> a,bigint<maxn> b){
        auto res=bigint<maxn>();
        cir(i,0,maxn) cir(j,0,maxn-i) res[i+j]+=a[i]*b[j];
        auto w=0;
        cir(i,0,maxn){
            res[i]+=w;
            w=res[i]/10;
            res[i]%=10;
        }
        return res;
    }
    bigint(){memset(this->data(),0,sizeof(*this));}
    bigint(int64_t w){
        cir(i,0,maxn) (*this)[i]=w%10,w/=10;
    }
};
template<const int maxn>
auto&operator<<(ostream&os,bigint<maxn> a){
    auto p=maxn-1;
    while(p&&(!a[p])) --p;
    for(auto i=p;~i;--i) os<<a[i];
    return os;
}
static constexpr auto maxn=207;
static constexpr auto maxb=512;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        auto uw=bigint<maxb>(1),dw=bigint<maxb>(1);
        auto ug=max(k-n+1,0);
        cir(i,0,n-1) uw=uw*(k+1);
        cir(i,0,n){
            const auto g=__gcd(ug,k);
            dw=dw*(k/g);
            ug/=g;
        }
        cout<<uw*ug<<' '<<dw<<'\n';
    }();
    return 0;
}
