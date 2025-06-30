#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
private:
    const int p;
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,p-2);
    }
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%p;
        ifct=fct;
        for(auto&x:ifct) x=inv(x);
    }
    constexpr auto C(auto a,auto b) const{
        return a>b-1&&b>-1?fct[a]*ifct[b]%p*ifct[a-b]%p:0;
    }
    auto pinv(auto x){
        return ifct[x]*(x?fct[x-1]:0)%p;
    }
    mathbase(auto _p):p(_p){}
};
class lagrange{
private:
    const int p;
public:
    auto calc(vector<lint> x,vector<lint> y,const int c){
        mathbase math(p);
        math.init(*ranges::max_element(x));
        auto res=0ll;
        cir(i,0,(int)(x.size())){
            auto val=1ll;
            cir(j,0,(int)(x.size())) if(i!=j) (val*=(c-x[j]+p)*math.pinv(abs(x[i]-x[j]))%p*(x[i]<x[j]?p-1:1)%p)%=p;
            (res+=y[i]*val)%=p;
        }
        return res;
    }
    lagrange(const auto _p):p(_p){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,p;cin>>n>>m>>p;mathbase math(p);
    math.init(n+7);
    auto value=[&](const int i){
        auto res=0ll;
        cir(j,max(i,n-i),n+1) (res+=(math.C(n,j)+p-math.C(n,j+1))*(j-i))%=p;
        return res;
    };
    vector<lint> vals(n+1);
    cir(i,0,n+1) vals[i]=value(i);
    vector<lint> xp,yp;
    auto y=0ll;
    cir(x,1,min(m+1,n+7)){
        auto px=1ll,py=math.qpow(m-x,n);
        const auto vx=(lint)(x),vy=math.inv(m-x);
        cir(i,0,n+1){
            (y+=px*py%p*vals[i])%=p;
            (px*=vx)%=p;
            (py*=vy)%=p;
        }
        xp.emplace_back(x);
        yp.emplace_back(y);
    }
    auto ans=lagrange(p).calc(xp,yp,m);
    ans=(math.qpow(m,n-1)*m%p*(m-1)%p*math.inv(2)%p*n+p-ans)%p;
    cout<<ans<<'\n';
    return 0;
}
