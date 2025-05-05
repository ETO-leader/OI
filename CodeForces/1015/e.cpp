#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct.resize(n);
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    auto C(const auto a,const auto b) const{
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
    auto fact(const auto x) const{return x>-1?fct[x]:0;}
} math;
using complf=complex<double>;
class basic_poly{
private:
    static constexpr auto pi=acosl(-1);
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=((rev[i>>1]>>1)|((n>>1)*(i&1)));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complf(cos(pi*2/h),sin(pi*2*type/h));
            for(auto i=0;i<n;i+=h){
                auto u=complf(1,0);
                cir(k,i,i+midh){
                    const auto wy=u*a[k+midh];
                    a[k+midh]=a[k]-wy;a[k]+=wy;
                    u*=wx;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
public:
    auto mul(vector<lint> a,vector<lint> b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> fx(n);
        cir(i,0,(int)(a.size())) fx[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) fx[i]+=complf(0,b[i]);
        fft<1>(fx,n);
        for(auto&i:fx) i*=i;
        fft<-1>(fx,n);
        vector<lint> res(n);
        cir(i,0,n) res[i]=roundl(fx[i].imag()/2);
        return res;
    }
} poly;
static constexpr auto maxn=5007;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    math.init(maxn);
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        const auto m=ranges::count(a,-1);
        vector<lint> cur(m+1);
        vector<lint> qans(m+1);
        cir(i,0,n){
            if(a[i]==-1){
                for(auto i=m;i;--i) (cur[i]+=cur[i-1])%=MOD;
                (++cur[1])%=MOD;
            }
            ++cur[0];
            cir(i,0,m+1) (qans[i]+=cur[i])%=MOD;
        }
        auto ans=0ll;
        vector<int> pos(n,-1);
        cir(i,0,n) if(a[i]>-1) pos[a[i]]=i;
        cir(w,1,n+1){
            auto l=n,r=0,cnt=0;
            cir(x,0,w) if(pos[x]>-1){
                l=min(l,pos[x]);
                r=max(r,pos[x]);
            }else{
                ++cnt;
            }
            if(l>r){
                cir(c,cnt,cnt+1) (ans+=qans[c]*math.fact(m-c)%MOD*math.fact(c))%=MOD;
            }else{
                auto mc=0;
                cir(i,l,r+1) mc+=(a[i]==-1);
                vector<lint> al(l+1),ar(n-r+1);
                auto wcnt=0;
                al[0]=ar[0]=1;
                for(auto i=l-1;~i;--i) wcnt+=(a[i]==-1),++al[wcnt];
                wcnt=0;
                cir(i,r+1,n) wcnt+=(a[i]==-1),++ar[wcnt];
                const auto res=poly.mul(al,ar);
                cir(i,0,(int)(res.size())) if(res[i]) (ans+=(res[i]%MOD)*math.C(i+mc,cnt)%MOD*math.fact(m-cnt)%MOD*math.fact(cnt))%=MOD;
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
