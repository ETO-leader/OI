#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(998244353);
class poly:public vector<lint>{
private:
    static constexpr auto inv2=(MOD+1)/2;
    using vector<lint>::vector;
    template<const int _type>
    static auto fwtor(poly&a,const int n){
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh) (a[k+midh]+=_type*a[k])%=MOD;
            }
        }
    }
    template<const int _type>
    static auto fwtand(poly&a,const int n){
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh) (a[k]+=_type*a[k+midh])%=MOD;
            }
        }
    }
    template<const int _type>
    static auto fwtxor(poly&a,const int n){
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto val=a[k];
                    (a[k]+=a[k+midh])%=MOD;
                    (a[k+midh]=val+MOD-a[k+midh])%=MOD;
                    (a[k]*=_type)%=MOD;
                    (a[k+midh]*=_type)%=MOD;
                }
            }
        }
    }
public:
    friend auto operator&(poly a,poly b){
        poly::fwtand<1>(a,(int)(a.size()));
        poly::fwtand<1>(b,(int)(b.size()));
        cir(i,0,(int)(a.size())) (a[i]*=b[i])%=MOD;
        poly::fwtand<MOD-1>(a,(int)(a.size()));
        return a;
    }
    friend auto operator|(poly a,poly b){
        poly::fwtor<1>(a,(int)(a.size()));
        poly::fwtor<1>(b,(int)(b.size()));
        cir(i,0,(int)(a.size())) (a[i]*=b[i])%=MOD;
        poly::fwtor<MOD-1>(a,(int)(a.size()));
        return a;
    }
    friend auto operator^(poly a,poly b){
        poly::fwtxor<1>(a,(int)(a.size()));
        poly::fwtxor<1>(b,(int)(b.size()));
        cir(i,0,(int)(a.size())) (a[i]*=b[i])%=MOD;
        poly::fwtxor<inv2>(a,(int)(a.size()));
        return a;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;poly a(1<<n),b(1<<n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    a=a|b;
    for(auto&i:a) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
