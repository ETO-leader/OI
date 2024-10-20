#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    static constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
} math;
class matrix{
private:
    vector<vector<lint>> a;
    auto I() const{
        auto res=matrix(a.size());
        cir(i,0,(int)(a.size())) res.a[i][i]=1;
        return res;
    }
public:
    auto&operator[](auto p){return a[p];}
    const auto&operator[](auto p) const{return a[p];}
    auto operator*(const matrix x) const{
        auto res=matrix(a.size());
        const auto n=(int)(a.size());
        cir(k,0,n) cir(i,0,n) cir(j,0,n){
            (res[i][j]+=a[i][k]*x[k][j])%=MOD;
        }
        return res;
    }
    auto pow(auto b) const{
        auto res=I(),pw=*this;
        while(b){
            if(b&1) res=res*pw;
            pw=pw*pw;b>>=1;
        }
        return res;
    }
    matrix(auto _n):a(_n,vector<lint>(_n)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        lint n,x,k;cin>>n>>x>>k;
        auto ans=math.qpow(k*2+1,n-1)*(k+x);
        auto s=matrix(x+1),f=matrix(x+1);
        cir(i,0,x) s[0][i]=1;
        cir(i,0,x) cir(j,0,x) if(abs(i-j)<k+1) f[i][j]=1;
        const auto ansa=s*(f.pow(n-1));
        (ans+=MOD-accumulate(ansa[0].begin(),ansa[0].end(),0ll)%MOD)%=MOD;
        println("{}",ans);
    }();
    return 0;
}
