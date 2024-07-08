#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
using complf=complex<lf>;
class basic_poly{
private:
    static constexpr auto pi=acosl(-1);
    vector<complf> wn;
    auto init(const int n){
        wn.resize(n);
        cir(i,0,n) wn[i]=complf(cosl(pi/n*i),sinl(pi/n*i));
    }
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        if(wn.size()<n) init(n);
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wy=((type==-1)?conj(wn[n*2/h*(k-i)]):
                        wn[n*2/h*(k-i)])*a[k+midh];
                    a[k+midh]=a[k]-wy;a[k]+=wy;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
    auto mulmn(vector<lf> a,vector<lf> b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> fx(n);
        cir(i,0,(int)(a.size())) fx[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) fx[i]+=complf(0,b[i]);
        fft<1>(fx,n);
        for(auto&i:fx) i*=i;
        fft<-1>(fx,n);
        vector<lf> res(n);
        cir(i,0,n) res[i]=fx[i].imag()/2;
        return res;
    }
    template<typename _Ty>
    auto rfloor(_Ty a){
        if(a<0) return floorl(a)-1;
        return floorl(a);
    }
    static constexpr auto spl=1000.0l;
public:
    auto mul(vector<lf> a,vector<lf> b){
        auto ax=a,ay=a;
        for(auto&i:ax) i=i-spl*floorl(i/spl);
        for(auto&i:ay) i=rfloor(i/spl);
        const auto ak=mulmn(ax,b),ar=mulmn(ay,b);
        vector<lf> ans(ak.size());
        cir(i,0,(int)(ak.size())){
            ans[i]=ak[i]+ar[i]*spl;
        }
        return ans;
    }
} poly;
template<typename _Ty>
constexpr auto sign(_Ty x){return _Ty(x<0?-1:1);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<lf> a(n),b;
    cir(i,0,n) cin>>a[i];
    cir(i,-n,n+1) b.push_back(i?sign(i)*1.0/i/i:0.0);
    cout<<fixed<<setprecision(15);
    auto ans=poly.mul(a,b);
    cir(i,n,n*2) cout<<ans[i]<<'\n';
    return 0;
}
