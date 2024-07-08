#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class basic_math{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint a){
        return qpow(a,MOD-2);
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
                    a[k+midh]=(MOD+a[k]-wk)%MOD;
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
    auto fit(vector<lint> x){
        while((!x.empty())&&(!x.back())) x.pop_back();
        return x;
    }
public:
    auto mul(vector<lint> a,vector<lint> b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        return fit(a);
    }
} poly;
auto check(vector<int>&w,int l,int r){
    if(l==r){
        vector<lint> res(w[l]+1);
        res[0]=1;res[w[l]]=MOD-1;
        return res;
    }
    const auto mid=(l+r)/2;
    return poly.mul(check(w,l,mid),check(w,mid+1,r));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> w(n);
    for(auto&i:w) cin>>i;
    auto f=check(w,1,n-1);
    auto ans=0ll;
    cir(i,0,(int)(f.size()))
        (ans+=f[i]*w[0]%MOD*math.inv(w[0]+i))%=MOD; 
    cout<<ans<<'\n';
    return 0;
}
