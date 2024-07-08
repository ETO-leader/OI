#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using complf=complex<long double>;
namespace poly{
    static constexpr auto pi=acosl(-1);
    static constexpr auto imod=1<<16;
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n){
            rev[i]=(rev[i>>1]>>1)|((n/2)*(i&1));
        }
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complf(cosl(pi*2/h),sinl(pi*2*type/h));
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
    template<typename restype>
    auto inmul(vector<int> a,vector<int> b,const int p){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> fx(n);
        cir(i,0,(int)(a.size())) fx[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) fx[i]+=complf(0,b[i]);
        fft<1>(fx,n);
        for(auto&i:fx) i*=i;
        fft<-1>(fx,n);
        vector<restype> ans(n);
        cir(i,0,n) ans[i]=(restype)(floorl(fx[i].imag()/2+0.6l))%p;
        return ans;
    }
    auto mul(vector<int> a,vector<int> b,const int p){
        auto ax=a,ay=a,bx=b,by=b;
        for(auto&i:ax) i%=imod;
        for(auto&i:ay) i/=imod;
        for(auto&i:bx) i%=imod;
        for(auto&i:by) i/=imod;
        auto mxx=inmul<__int128_t>(ax,bx,p),
            mxy=inmul<__int128_t>(ax,by,p),
            myx=inmul<__int128_t>(ay,bx,p),
            myy=inmul<__int128_t>(ay,by,p);
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<int> res(n);
        cir(i,0,n){
            res[i]=(mxx[i]+mxy[i]*imod+
                myx[i]*imod+myy[i]*imod*imod)%p;
        }
        return res;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,p;cin>>n>>m>>p;
    vector<int> a(n),b(m);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    auto ans=poly::mul(a,b,p);
    cir(i,0,n+m-1) cout<<ans[i]<<' ';
    cout<<'\n';
    return 0;
}
