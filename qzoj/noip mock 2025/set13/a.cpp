#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;i++)
using namespace std;
using lint=long long;
static constexpr auto MOD=2147483647;
class poly:public vector<lint>{
private:
    using vector<lint>::vector;
    template<const int type>
    static auto bfwt(poly&x){
        const auto n=(int)(x.size());
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h) cir(k,0,midh){
                (x[i+midh+k]+=type*x[i+k])%=MOD;
            }
        }
    }
public:
    auto fwt(){
        poly::bfwt<1>(*this);
    }
    auto ifwt(){
        poly::bfwt<-1>(*this);
    }
    auto dot(const poly x) const{
        auto res=*this;
        cir(i,0,(int)(x.size())) (res[i]*=x[i])%=MOD;
        return res;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,w;cin>>n>>w;
    auto cost=poly(1<<n);
    cir(i,0,n) cin>>cost[1<<i];
    cost.fwt();
    auto valid=poly(1<<n);
    cir(s,0,(1<<n)) if(cost[s]<w+1){
        valid[s]=1;
    }
    valid.fwt();
    auto f=poly(1<<n);
    f[0]=1;
    f.fwt();
    auto ans=-1;
    cir(i,0,n){
        f=f.dot(valid);
        auto nf=f;
        nf.ifwt();
        if(nf[(1<<n)-1]){
            ans=i+1;
            break;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
