#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
constexpr auto qpow(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
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
            const auto wx=qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ll;
                cir(k,i,i+midh){
                    const auto wy=(a[k+midh]*u)%MOD;
                    a[k+midh]=(a[k]+MOD-wy)%MOD;
                    (a[k]+=wy)%=MOD;
                    (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            const auto invn=inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=invn)%=MOD;
        }
    }
public:
    auto mul(vector<lint>&a,vector<lint>&b){
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
auto divide(int l,int r,vector<lint>&ans){
    if(l==r||r<2) return;
    const auto mid=(l+r)/2;
    divide(l,mid,ans);
    (ans[mid+1]+=mid*ans[mid])%=MOD;
    auto check=[&](const bool cka){
        auto arra=vector<lint>(ans.begin(),ans.begin()+min(r-l+1,mid+1));
        auto arrb=vector<lint>(ans.begin()+l,ans.begin()+mid+1);
        if(cka) cir(i,0,(int)(arra.size())) (arra[i]*=(i-1))%=MOD;
        else cir(i,0,(int)(arrb.size())) (arrb[i]*=(l+i-1))%=MOD;
        arra[1]=0;
        cir(i,0,2-l) arrb[i]=0;
        auto delta=poly.mul(arra,arrb);
        cir(i,mid+1,r+1){
            (ans[i]+=delta[i-l])%=MOD;
        }
    };
    check(true);
    if(l) check(false);
    divide(mid+1,r,ans);
}
static constexpr auto maxq=1<<17;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    vector<lint> ansi(maxq);
    ansi[0]=1;ansi[1]=2;
    divide(0,maxq-1,ansi);
    while(T--) [&](){
        int n;cin>>n;
        cout<<ansi[n]<<'\n';
    }();
    return 0;
}
