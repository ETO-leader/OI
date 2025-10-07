#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<class fft_type=long double>
class poly:public vector<fft_type>{
private:
    using vector<fft_type>::vector;
    using complf=complex<fft_type>;
    static constexpr auto pi=acosl(-1);
    auto change(vector<complf>&a,const auto n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const auto n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=complf(
                cosl(pi*2/h),
                sinl(pi*2*type/h)
            );
            for(auto i=0;i<n;i+=h){
                auto u=complf(1,0);
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
    auto sized(const auto n){
        auto a=*this;a.resize(n);
        return a;
    }
    friend auto operator+(poly a,poly b){
        a.resize(max(a.size(),b.size()));
        cir(i,0,(int)(b.size())) a[i]+=b[i];
        return a;
    }
    friend auto operator-(poly a){
        for(auto&i:a) i=-i;
        return a;
    }
    friend auto operator-(poly a,poly b){
        return a+(-b);
    }
    friend auto operator*(poly a,auto b){
        for(auto&i:a) i*=b;
        return a;
    }
    friend auto operator*(poly a,poly b){
        const auto n=1<<(int)(ceil(log2(a.size()+b.size())));
        vector<complf> x(n);
        cir(i,0,(int)(a.size())) x[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) x[i]+=complf(0,b[i]);
        a.fft<1>(x,n);
        for(auto&i:x) i*=i;
        a.fft<-1>(x,n);
        auto res=poly(n);
        cir(i,0,n) res[i]=imag(x[i])/2;
        return res;
    }
    auto shift(){
        auto a=*this;
        a.emplace(a.begin(),0);
        return a;
    }
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> siz,ban;
    auto dfssz(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&v:gr[u]) if(v!=f&&(!ban[v])) siz[u]+=dfssz(v,u);
        return siz[u];
    }
    auto dfsrt(int u,const int tsiz,int f=-1)->int{
        auto umx=-1;
        for(auto&v:gr[u]) if(v!=f&&(!ban[v])){
            const auto vw=dfsrt(v,tsiz,u);
            if(vw>-1) return vw;
            umx=max(umx,siz[v]);
        }
        if(max(umx,tsiz-siz[u])<tsiz/2+1) return u;
        return -1;
    }
    auto dfsht(int u,int dep,poly<long double>&uf,int f=-1)->void{
        ++dep;
        while((int)(uf.size())<dep+1) uf.emplace_back(0);
        ++uf[dep];
        for(auto&v:gr[u]) if(v!=f&&(!ban[v])) dfsht(v,dep,uf,u);
    }
    auto divide(int u,poly<long double>&ans){
        const auto tsiz=dfssz(u);
        if(tsiz==1) return;
        const auto rt=dfsrt(u,tsiz);
        ban[rt]=true;
        poly<long double> cur(1,1);
        sort(gr[rt].begin(),gr[rt].end(),[&](auto u,auto v){
            return siz[u]<siz[v];
        });
        for(auto&v:gr[rt]) if(!ban[v]){
            auto uf=poly<long double>(1);
            dfsht(v,0,uf,rt);
            ans=ans+(cur*uf).shift();
            cur=cur+uf;
        }
        for(auto&v:gr[rt]) if(!ban[v]) divide(v,ans);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto count(){
        poly<long double> ans;
        divide(0,ans);
        auto res=0.0l;
        cir(i,1,(int)(ans.size())) res+=ans[i]/i;
        return res*2+(int)(gr.size());
    }
    tree(int _n):gr(_n),siz(_n),ban(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        gr.link(u,v);
    }
    cout<<fixed<<setprecision(4)<<gr.count()<<'\n';
    return 0;
}
