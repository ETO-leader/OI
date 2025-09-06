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
    auto fact(auto x){
        return fct[x];
    }
    mathbase(auto _p):p(_p){}
};
class lagrange{
public:
    auto solve(vector<lint> a,vector<lint> xi,lint x,const int p){
        auto ans=0ll;
        mathbase math(p);
        cir(i,0,(int)(a.size())){
            auto prod=a[i];
            cir(j,0,(int)(a.size())) if(i!=j){
                (prod*=(x-xi[j]+p)*math.inv(xi[i]-xi[j]+p)%p)%=p;
            }
            (ans+=prod)%=p;
        }
        return ans;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int k,n,p;cin>>k>>n>>p;
    mathbase math(p);
    math.init(n+7);
    vector<vector<lint>> f(n+1,vector<lint>(n*2+7));
    f[0][0]=1;
    cir(i,0,n){
        cir(j,i,n*2+7) cir(k,j+1,n*2+7){
            f[i+1][k]+=f[i][j]*k;
        }
        cir(k,i,n*2+7) (f[i+1][k])%=p;
    }
    cir(i,1,n*2+7) (f[n][i]+=f[n][i-1])%=p;
    vector<lint> px(n*2+7);
    iota(px.begin(),px.end(),0);
    cout<<lagrange().solve(f[n],px,k,p)*math.fact(n)%p<<'\n';
    return 0;
}
