#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
static constexpr auto maxq=(int)(1e5+7);
class basic_math{
private:
    vector<lint> fct;
    auto initfct(const int n){
        if(fct.empty()) fct.push_back(1);
        while((int)(fct.size())<n+1){
            fct.push_back(fct.back()*fct.size()%MOD);
        }
    }
public:
    static constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        for(;a<0;a+=MOD);
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    static constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
    auto fact(const int n){
        initfct(n);
        return fct[n];
    }
} math;
class basic_poly{
private:
    auto change(vector<lint>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(vector<lint>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ll;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    a[k+midh]=(a[k]+MOD-wk)%MOD;
                    (a[k]+=wk)%=MOD;
                    (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            const auto invx=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=invx)%=MOD;
        }
    }
public:
    auto mul(const vector<lint>&a,const vector<lint>&b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<lint> ax(n),bx(n);
        cir(i,0,(int)(a.size())) ax[i]=a[i];
        cir(i,0,(int)(b.size())) bx[i]=b[i];
        ntt<1>(ax,n);ntt<1>(bx,n);
        cir(i,0,n) (ax[i]*=bx[i])%=MOD;
        ntt<-1>(ax,n);
        return ax;
    }
} poly;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> f(n+1),g(n+1);
    cir(i,0,n+1){
        f[i]=math.qpow(-1,i)*math.inv(math.fact(i))%MOD;
    }
    cir(i,0,n+1){
        g[i]=(math.qpow(i,n+1)+MOD-1)%MOD*
            math.inv((i+MOD-1)%MOD)%MOD*
            math.inv(math.fact(i))%MOD;
    }
    g[0]=1;g[1]=n+1;
    const auto ansa=poly.mul(f,g);
    auto ans=0ll;
    cir(i,0,n+1){
        (ans+=math.qpow(2,i)*
            math.fact(i)%MOD*ansa[i])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
