#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("wormhole.in");
ofstream ouf("wormhole.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
#define inf cin
#define ouf cout
#endif
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=(int)(998244353);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn;
    map<tuple<int,int,int>,uint64_t> val;
    mt19937_64 eng;
    auto dfs(int u,vector<int>&ins,auto&cnt)->void{
        ins.emplace_back(u);
        dfn[u]=++cnt;
        for(auto&[w,v]:gr[u]) if(!dfn[v]) dfs(v,ins,cnt);
    }
    auto gethash(vector<int> ins){
        auto res=0ull;
        for(auto&u:ins) for(auto&[w,v]:gr[u]){
            if(!val.count({dfn[u],dfn[v],w})) val[{dfn[u],dfn[v],w}]=eng();
            res^=val[{dfn[u],dfn[v],w}];
        }
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(w,v);
    }
    auto check(){
        map<uint64_t,int> siz,cnt;
        for(auto&x:gr) ranges::sort(x);
        cir(i,0,(int)(gr.size())) if(!dfn[i]){
            vector<int> ins;auto cnti=0;
            dfs(i,ins,cnti);
            const auto w=gethash(ins);
            siz[w]=ins.size();
            ++cnt[w];
        }
        return pair(siz,cnt);
    }
    graph(int _n):gr(_n),dfn(_n),eng(random_device().operator()()){}
};
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
using poly=vector<lint>;
class polybase{
private:
    auto change(poly&a,const auto n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ll;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    (a[k+midh]=a[k]+MOD-wk)%=MOD;
                    (a[k]+=wk)%=MOD;
                    (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            const auto ivn=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=ivn)%=MOD;
        }
    }
public:
    auto mul(poly a,poly b){
        const auto n=1<<(int)(ceil(log2(a.size()+b.size())));
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        while((a.size()>1)&&(!a.back())) a.pop_back();
        return a;
    }
} polys;
auto operator*(const poly a,const poly b){
    return polys.mul(a,b);
}
auto operator+(poly a,poly b)->poly{
    if(a.size()<b.size()) return b+a;
    cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
    return a;
}
auto operator-(poly a){
    for(auto&i:a) i=i?MOD-i:0;
    return a;
}
auto fitlen(poly x,const auto n){
    x.resize(n);
    return x;
}
auto inv(poly a,const auto n){
    auto res=poly{math.inv(a[0])};
    a.resize(1<<(int)(ceil(log2(a.size()))));
    for(auto i=1;i<n;i<<=1) res=fitlen(res*fitlen(-(a*res)+poly{2},i<<1),i<<1);
    return fitlen(res,n);
}
auto inv(poly a){return inv(a,a.size());}
auto deriv(poly a){
    const auto n=(int)(a.size());
    auto res=poly(n-1);
    cir(i,1,n) res[i-1]=a[i]*i%MOD;
    return res;
}
auto intge(poly a){
    const auto n=(int)(a.size());
    auto res=poly(n+1);
    cir(i,0,n) res[i+1]=a[i]*math.inv(i+1)%MOD;
    return res;
}
auto ln(poly a){
    return intge(deriv(a)*inv(a));
}
auto exp(poly a){
    auto res=poly{1};
    a.resize(1<<(int)(ceil(log2(a.size()))));
    const auto n=(int)(a.size());
    for(auto i=1;i<n;i<<=1){
        res=fitlen(res*(poly{1}+(-ln(fitlen(res,i<<1)))+a),i<<1);
    }
    return res;
}
auto check(const auto siz,const auto n,const auto k){
    vector<vector<int>> d(n+1);
    cir(i,1,n+1){
        for(auto j=i;j<n+1;j+=i) d[j].emplace_back(i);
    }
    poly ans(n+1);
    vector<vector<lint>> f(n+1);
    ans[1]=math.qpow(siz,k);
    f[1].emplace_back(siz);
    vector<int> id(n+1);
    cir(i,2,n+1){
        f[i].resize(d[i].size());
        for(auto cnt=-1;auto&v:d[i]) id[v]=++cnt;
        for(auto&v:d[i]) if(v<i) for(auto p=-1;auto&x:d[v]){
            ++p;
            (f[i][id[x]]+=f[v][p])%=MOD;
        }
        for(auto p=-1;auto&v:d[i]){
            if(++p;v<i){
                const auto w=f[i][p]*math.inv(siz)%MOD*(MOD-math.inv(i-v))%MOD;
                f[i][p]=w;(f[i][d[i].size()-1]+=(MOD-w))%=MOD;
            }
            (ans[i]+=f[i][p]*math.qpow(v,k)%MOD*math.qpow(siz,k))%=MOD;
        }
        (ans[i]*=math.inv(i)*math.qpow(siz,i-1)%MOD)%=MOD;
        for(auto&w:f[i]) (w*=i*siz%MOD)%=MOD;
    }
    return exp(ans);
}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,n,m;lint k;inf>>c>>n>>m>>k;
    graph gr(n);
    cir(i,0,n*m){
        int u,v,w;inf>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    auto[siz,cnt]=gr.check();
    auto ans=1ll;
    for(auto&[w,sz]:siz){
        (ans*=check(sz,cnt[w],k)[cnt[w]]*[](auto x){
            auto res=1ll;
            cir(i,1,x+1) (res*=i)%=MOD;
            return res;
        }(cnt[w])%MOD)%=MOD;
    }
    ouf<<ans<<'\n';
    return 0;
}
