#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
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
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&i:ifct) i=inv(i);
    }
    auto C(auto a,auto b){
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
auto gmethod(const int n,vector<lint> a,vector<lint> b){
    vector<lint> f(n+1);
    const auto lx=n/(int)(a.size());
    f[0]=1;
    cir(i,0,(int)(a.size())){
        const auto lf=f;
        ranges::fill(f,0);
        cir(w,0,n) cir(k,0,a[i]+1) if(w+k+(b[i]-(a[i]-k))<n+1&&w+k+(b[i]-(a[i]-k))>-1){
            (f[w+k+(b[i]-(a[i]-k))]+=lf[w]*math.C(a[i],k)%MOD*math.C(lx-a[i],b[i]-(a[i]-k)))%=MOD;
        }
    }
    for(auto&i:f) (i*=math.qpow(math.inv(2),n))%=MOD;
    return f;
}
using poly=vector<lint>;
// slow mode (O(|a||b|))
auto operator*(poly a,poly b){
    auto res=poly(a.size()+b.size()-1);
    cir(i,0,(int)(a.size())) cir(j,0,(int)(b.size())){
        (res[i+j]+=a[i]*b[j])%=MOD;
    }
    while(!res.back()) res.pop_back();
    return res;
};
// slow mode (O(|a||b|+logP))
auto operator/(poly a,poly b){
    auto res=poly(a.size());
    const auto lb=(int)(b.size());
    const auto ivbl=math.inv(b[lb-1]);
    for(auto i=(int)(a.size())-1;i>lb-2;--i){
        const auto w=a[i]*ivbl%MOD;
        res[i-lb+1]=w;
        for(auto j=i;j>i-lb;--j) (a[j]+=MOD-b[lb+j-i-1]*w)%=MOD;
    }
    while(!res.back()) res.pop_back();
    return res;
};
// B = (x + 1)
auto powerB(const auto k){
    auto res=poly(k+1);
    cir(i,0,k+1) res[i]=math.C(k,i);
    return res;
}
// C()
auto polyC(vector<lint> c){
    const auto n=(int)(c.size())-1;
    auto cur=powerB(n);
    auto res=poly(n+1);
    cir(i,0,n+1){
        cir(p,0,(int)(cur.size())) (res[p]+=c[i]*cur[p])%=MOD;
        cur=cur*poly{1,MOD-1}/poly{1,1};
    }
    res.resize(c.size());
    ranges::reverse(res);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int h,w;cin>>h>>w;
    const auto n=h*w;
    math.init(n+7);
    vector<string> s(h);
    for(auto&i:s) cin>>i;
    vector<lint> a(h),b(h);
    for(auto&i:b) cin>>i;
    cir(i,0,h) a[i]=ranges::count(s[i],'1');
    const auto A_c=gmethod(n,a,b);
    const auto B_c=gmethod(n,b,b);
    const auto CA=polyC(A_c);
    const auto CB=polyC(B_c);
    auto pA=CA[n],pAd=0ll,pB=CB[n],pBd=0ll;
    cir(k,0,n){
        const auto t=(k*2+MOD-n)*math.inv(n)%MOD;
        (pAd+=CA[k]*math.inv((t+MOD-1)%MOD))%=MOD;
        (pBd+=CB[k]*math.inv((t+MOD-1)%MOD))%=MOD;
    }
    const auto ans=(pAd*pB%MOD+MOD-pBd*pA%MOD)%MOD*math.inv(pB*pB%MOD)%MOD;
    cout<<ans<<'\n';
    return 0;
}
