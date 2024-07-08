#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using complf=complex<double>;
class basic_poly{
private:
    static constexpr auto pi=acosl(-1);
    vector<complf> wn;
    auto init(const int n){
        wn.resize(n);
        cir(i,0,n) wn[i]=complf(cos(pi/n*i),sin(pi/n*i));
    }
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n){
            rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
        }
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        if((int)(wn.size())<n) init(n);
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
    static constexpr auto imod=1<<15;
public:
    auto mul(const vector<int>&a,const vector<int>&b,const int p){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> ax(n),bx(n),cx(n),dx(n);
        cir(i,0,(int)(a.size())) ax[i]=complf(a[i]/imod,a[i]%imod);
        cir(i,0,(int)(b.size())) cx[i]=complf(b[i]/imod,b[i]%imod);
        fft<1>(ax,n);fft<1>(cx,n);
        cir(i,1,n) bx[i]=conj(ax[n-i]);
        cir(i,1,n) dx[i]=conj(cx[n-i]);
        bx[0]=conj(ax[0]);dx[0]=conj(cx[0]);
        cir(i,0,n){
            const auto
                af=(ax[i]+bx[i])*complf(0.5,0),
                bf=(ax[i]-bx[i])*complf(0,-0.5),
                cf=(cx[i]+dx[i])*complf(0.5,0),
                df=(cx[i]-dx[i])*complf(0,-0.5);
            ax[i]=(af*cf)+(af*df+bf*cf)*complf(0,1),bx[i]=bf*df;
        }
        fft<-1>(ax,n);fft<-1>(bx,n);
        vector<int> ans(n);
        cir(i,0,n){
            const auto
                wx=(long long)(floor(ax[i].real()+0.6l))%p,
                wy=(long long)(floor(ax[i].imag()+0.6l))%p,
                wz=(long long)(floor(bx[i].real()+0.6l))%p;
            ans[i]=(wx*imod*imod+wy*imod+wz)%p;
        }
        return ans;
    }
} polyop;
class poly{
private:
    vector<int> a;int p;
public:
    auto&at(int x){return a[x];}
    auto operator*(const poly x) const{
        poly res(a.size(),p);
        const auto nresa=polyop.mul(a,x.a,p);
        cir(i,0,(int)(a.size())) res.a[i]=nresa[i];
        return res;
    }
    poly(int n,int _p):a(n),p(_p){}
};
auto staticpoly(int n,int p,bool x=false){
    poly res(n,p);res.at(0)=1;
    if(x) res.at(1)=1;
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,p;cin>>n>>m>>p;++m;
    auto pw=staticpoly(m,p,true),ans=staticpoly(m,p);
    cir(i,0,30){
        if(n&(1<<i)) ans=ans*pw;
        pw=pw*pw;
    }
    cir(i,0,m) cout<<ans.at(i)<<' ';
    cout<<'\n';
    return 0;
}
