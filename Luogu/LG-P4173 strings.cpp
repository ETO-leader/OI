#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto pi=numbers::pi_v<long double>;
class poly:public vector<lint>{
private:
    using vector<lint>::vector;
    static auto change(auto&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(rev[i]<i) std::swap(a[i],a[rev[i]]);
    }
    template<const int type>
    static auto fft(vector<complex<long double>>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complex<long double>(cosl(pi*2/h),sinl(pi*2*type/h));
            for(auto i=0;i<n;i+=h){
                auto u=complex<long double>(1,0);
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
    friend auto operator*(poly a,poly b){
        const auto n=1<<(int)(ceil(log2(a.size()+b.size())));
        auto f=vector<complex<long double>>(n);
        cir(i,0,(int)(a.size())) f[i]+=complex<long double>(a[i],0);
        cir(i,0,(int)(b.size())) f[i]+=complex<long double>(0,b[i]);
        fft<1>(f,n);
        cir(i,0,n) f[i]*=f[i];
        fft<-1>(f,n);
        auto res=poly(n);
        cir(i,0,n) res[i]=roundl(imag(f[i])/2);
        return res;
    }
    friend auto operator+(poly a,poly b){
        a.resize(max(a.size(),b.size()));
        cir(i,0,(int)(a.size())) a[i]+=b[i];
        return a;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>m>>n;
    string a,b;cin>>b>>a;
    auto f=poly(n),g=poly(m);
    cir(i,0,n) f[i]=(a[i]=='*'?0:a[i]-'a'+1);
    cir(i,0,m) g[m-i-1]=(b[i]=='*'?0:b[i]-'a'+1);
    const auto result=[&]{
        auto uf=f,ug=g;
        cir(i,0,n) uf[i]=uf[i]*uf[i]*uf[i];
        return uf*ug;
    }()+[&]{
        auto uf=f,ug=g;
        cir(i,0,n) uf[i]=-uf[i]*uf[i]*2;
        cir(i,0,m) ug[i]=ug[i]*ug[i];
        return uf*ug;
    }()+[&]{
        auto uf=f,ug=g;
        cir(i,0,m) ug[i]=ug[i]*ug[i]*ug[i];
        return uf*ug;
    }();
    vector<int> ans;
    cir(i,0,n-m+1) if(!result[i+m-1]) ans.emplace_back(i+1);
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
