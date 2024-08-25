#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using poly=vector<lint>;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
public:
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
            vector<lint> pw(midh);
            auto u=1ll;
            cir(i,0,midh) pw[i]=u,(u*=wx)%=MOD;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*pw[k-i]%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=(a[k+midh]>MOD-1?MOD:0);
                    a[k]+=wk;
                    a[k]-=(a[k]>MOD-1?MOD:0);
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
        for(auto&i:a) i=+MOD-i;
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
        poly res{math.inv(a[0])};
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
        while((a.size()>1)&&(!(a.back()%MOD))) a.pop_back();
        return a;
    }
    const auto dot(poly a,poly b){
        auto res=0ll;
        assert(a.size()==b.size());
        cir(i,0,(int)(a.size())) (res+=a[i]*b[i])%=MOD;
        return res;
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
        reverse(a.begin(),a.end());
        auto res=poly{1},pw=poly{0,1};
        while(b){
            if(b&1) res=res*pw%a;
            pw=pw*pw%a;b>>=1;
        }
        return res;
    }
} lnrc;
class berlekamp_massey{
public:
    auto solve(vector<lint> a){
        auto p=poly(),las=poly();
        auto k=-1ll,delta=0ll;
        for(auto i=-1;auto&x:a){
            ++i;
            auto nw=0ll;
            cir(j,0,(int)(p.size())){
                (nw+=p[j]*a[i-j-1])%=MOD;
            }
            if(nw==x) continue;
            if(k<0){
                k=i;
                delta=(x+MOD-nw)%MOD;
                p.resize(i+1);
                continue;
            }
            const auto w=(x+MOD-nw)*math.inv(delta)%MOD;
            const auto np=p;
            if(p.size()<las.size()+(i-k)) p.resize(las.size()+(i-k));
            (p[i-k-1]+=w)%=MOD;
            cir(j,0,(int)(las.size())){
                p[i+j-k]=(p[i+j-k]-w*las[j]%MOD+MOD)%MOD;
            }
            if((int)(np.size())-i<(int)(las.size())-k){
                las=np;k=i;
                delta=(x+MOD-nw)%MOD;
            }
        }
        for(auto&i:p) i=(MOD-i)%MOD;
        p.insert(p.begin(),1);
        return p;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<vector<pair<int,lint>>> gr(n);
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        gr[u-1].emplace_back(v-1,w);
    }
    vector<vector<lint>> a(n*2+7);
    vector<lint> f(n),aw(n*2+7);f[0]=1;
    poly rd(n);
    mt19937_64 rnd(
        #ifdef local_test
        251
        #else
        random_device().operator()()
        #endif
    );
    for(auto&i:rd) i=rnd()%MOD;
    a[0]=f;
    aw[0]=polys.dot(a[0],rd);
    cir(i,1,n*2+7){
        a[i]=[&](){
            const auto g=f;
            fill(f.begin(),f.end(),0);
            cir(u,0,n){
                for(auto&[v,w]:gr[u]) (f[v]+=g[u]*w)%=MOD;
            }
            return f;
        }();
        aw[i]=polys.dot(a[i],rd);
    }
    auto p=berlekamp_massey().solve(aw);
    const auto w=lnrc.solve(p,k);
    auto ans=poly(n);
    cir(i,0,(int)(w.size())) ans=ans+a[i]*poly{w[i]};
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
