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
    poly<long double> a(n),b(n);
    cir(i,0,n) cin>>a[i]>>b[i];
    reverse(b.begin(),b.end());
    const auto x=a*b;
    cir(i,0,n) cout<<x[i+n-1]<<'\n';
    return 0;
}
