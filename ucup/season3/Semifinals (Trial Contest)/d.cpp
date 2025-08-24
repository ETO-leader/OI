#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename _Fp_t>
class poly:public vector<lint>{
private:
    static constexpr auto pi=acosl(-1);
    using vector<lint>::vector;
    static auto change(auto&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
    }
    template<const int type>
    static auto fft(vector<complex<_Fp_t>>&a,const int n){
        poly<_Fp_t>::change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complex<_Fp_t>(cos(pi*2/h),sin(pi*2*type/h));
            for(auto i=0;i<n;i+=h){
                auto u=complex<_Fp_t>(1,0);
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u;
                    a[k+midh]=a[k]-wk;
                    a[k]+=wk;
                    u*=wx;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
public:
    friend auto operator*(poly<_Fp_t> a,poly<_Fp_t> b){
        const auto n=1<<(int)(ceil(log2(max(a.size(),b.size())*2)));
        vector<complex<_Fp_t>> x(n);
        cir(i,0,(int)(a.size())) x[i]+=complex<_Fp_t>(a[i],0);
        cir(i,0,(int)(b.size())) x[i]+=complex<_Fp_t>(0,b[i]);
        poly<_Fp_t>::fft<1>(x,n);
        cir(i,0,n) x[i]*=x[i];
        poly<_Fp_t>::fft<-1>(x,n);
        poly<_Fp_t> res(n);
        cir(i,0,n) res[i]=roundl(imag(x[i])/2);
        return res;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<lint> a(n),b(n);
    static constexpr auto mv=(int)(1e3);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    auto A=poly<long double>(n),B=poly<long double>(n);
    auto C=poly<long double>(n),D=poly<long double>(n);
    cir(i,0,n) A[i]=a[i]%mv,B[i]=a[i]/mv;
    cir(i,0,n) C[i]=b[i]%mv,D[i]=b[i]/mv;
    const auto mAC=A*C;
    const auto mAD=A*D;
    const auto mBC=B*C;
    const auto mBD=B*D;
    vector<lint> ans(n);
    cir(i,0,(int)(mAC.size())) ans[i%n]+=mAC[i]+mAD[i]*mv+mBC[i]*mv+mBD[i]*mv*mv;
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
