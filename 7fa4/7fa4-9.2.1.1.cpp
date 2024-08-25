#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
using poly=vector<lint>;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
} math;
class polybase{
private:
    unordered_map<int,vector<int>> nrv;
    auto change(poly&a,const int n){
        if(!nrv.count(n)){
            vector<int> rev(n);
            cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
            nrv[n]=rev;
        }
        auto&rv=nrv[n];
        cir(i,0,n) if(i<rv[i]) swap(a[i],a[rv[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ull;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=(a[k+midh]>MOD-1?MOD:0);
                    a[k]+=wk;
                    a[k]-=(a[k]>MOD-1?MOD:0);
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
    auto fitlen(poly a,const int n){
        return a.resize(n),a;
    }
    auto neg(poly a){
        for(auto&i:a) i=(MOD-i)%MOD;
        return a;
    }
    auto addnum(poly a,int k){
        return a[0]+=k,a;
    }
public:
    auto sum(poly a,poly b)->poly{
        if(a.size()<b.size()) return sum(b,a);
        for(auto c=-1;auto&x:b) (a[++c]+=x)%=MOD;
        return a;
    }
    auto minus(poly a,poly b){
        return sum(a,neg(b));
    }
    auto mul(poly a,poly b){
        const auto n=1<<((int)(log2(a.size()+b.size())+1));
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        return a;
    }
    auto inv(poly a){
        const auto lasn=(int)(a.size());
        fitlen(a,1<<(int)(ceil(log2(a.size()))));
        const auto n=(int)(a.size());
        poly res(n);res[0]=math.inv(a[0]);
        for(auto i=1;i<n;i<<=1){
            res=fitlen(mul(res,fitlen(addnum(neg(mul(a,res)),2),i<<1)),i<<1);
        }
        return fitlen(res,lasn);
    }
    auto inv(poly a,const int lasn){
        return inv(fitlen(a,lasn));
    }
    auto div(poly f,poly g){
        const auto n=(int)(f.size()),m=(int)(g.size());
        const auto lf=f,lg=g;
        reverse(f.begin(),f.end());
        reverse(g.begin(),g.end());
        f.resize(max(n-m+1,1));
        g.resize(max(n-m+1,1));
        auto q=mul(f,inv(g));
        q.resize(max(n-m+1,1));
        reverse(q.begin(),q.end());
        f=lf;g=lg;
        return pair(q,minus(f,mul(g,q)));
    }
    auto removez(poly a){
        while((a.size()>1)&&(!a.back())) a.pop_back();
        return a;
    }
} polys;
auto operator+(const poly a,const poly b){
    return polys.removez(polys.sum(a,b));
}
auto operator-(const poly a,const poly b){
    return polys.removez(polys.minus(a,b));
}
auto operator*(const poly a,const poly b){
    return polys.removez(polys.mul(a,b));
}
auto operator/(const poly a,const poly b){
    return polys.removez(polys.div(a,b).first);
}
auto operator%(const poly a,const poly b){
    return polys.removez(polys.div(a,b).second);
}
class linear_recurrence{
public:
    auto solve(poly a,lint b){
        a[0]=MOD-1;
        reverse(a.begin(),a.end());
        auto res=poly{1},pw=poly{0,1};
        while(b){
            cerr<<b<<' '<<res.size()<<' '<<pw.size()<<'\n';
            if(b&1) res=res*pw%a;
            pw=pw*pw%a;b>>=1;
        }
        return res;
    }
} lnrc;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint m,l,r;cin>>m>>l>>r;
    auto f=poly(m);
    for(auto&i:f) cin>>i;
    f.insert(f.begin(),0);
    const auto a=polys.inv(poly{1}-f,r-l+m+7);
    while(l<m+1){
        cout<<a[l]<<'\n';
        if((++l)>r) exit(0);
    }
    auto warr=lnrc.solve(f,l);
    warr.resize(m+1);
    reverse(warr.begin(),warr.end());
    const auto ans=warr*a;
    cir(i,m,r-l+m+1) cout<<ans[i]<<'\n';
    return 0;
}
