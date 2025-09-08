#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("butterfly.in");
ofstream ouf("butterfly.out");
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto qpow(lint a,auto b,const int p) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
class barrett{
private:
    uint64_t m,p;
public:
    auto init(int x){
        m=((__uint128_t)(1)<<64)/x;
        p=x;
    }
    inline constexpr auto mod(uint64_t x) const{
        return (uint64_t)(x-(((__uint128_t)(x)*m)>>64)*p);
    }
};
barrett mod;
class berlekamp_massey{
public:
    auto solve(vector<lint> a){
        auto p=vector<lint>(),las=vector<lint>();
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
class matrix4:public array<array<unsigned lint,4>,4>{
public:
    auto mul(matrix4&b) const{
        auto res=matrix4();
        cir(k,0,4) cir(i,0,4){
            res[i][0]+=(*this)[i][k]*b[k][0];
            res[i][1]+=(*this)[i][k]*b[k][1];
            res[i][2]+=(*this)[i][k]*b[k][2];
            res[i][3]+=(*this)[i][k]*b[k][3];
        }
        cir(i,0,4){
            res[i][0]=mod.mod(res[i][0]);
            res[i][1]=mod.mod(res[i][1]);
            res[i][2]=mod.mod(res[i][2]);
            res[i][3]=mod.mod(res[i][3]);
        }
        return res;
    }
    auto mul_col(matrix4&b) const{
        auto res=matrix4();
        cir(k,0,4){
            res[0][0]+=(*this)[0][k]*b[k][0];
            res[0][1]+=(*this)[0][k]*b[k][1];
            res[0][2]+=(*this)[0][k]*b[k][2];
            res[0][3]+=(*this)[0][k]*b[k][3];
        }
        res[0][0]=mod.mod(res[0][0]);
        res[0][1]=mod.mod(res[0][1]);
        res[0][2]=mod.mod(res[0][2]);
        res[0][3]=mod.mod(res[0][3]);
        return res;
    }
    auto mulpow(matrix4 s,auto x,auto&upw) const{
        const auto n=(int)(this->size());
        auto cnt=0;
        while(x){
            if(x&1) s=s.mul_col(upw[cnt]);
            ++cnt;x>>=1;
        }
        return s;
    }
    matrix4(lint _v=0){
        memset(this->begin(),0,sizeof(*this));
        cir(i,0,4) (*this)[i][i]=_v; 
    }
};
class matrix3:public array<array<unsigned lint,3>,3>{
public:
    auto mul(matrix3&b) const{
        auto res=matrix3();
        cir(k,0,3) cir(i,0,3){
            res[i][0]+=(*this)[i][k]*b[k][0];
            res[i][1]+=(*this)[i][k]*b[k][1];
            res[i][2]+=(*this)[i][k]*b[k][2];
        }
        cir(i,0,3){
            res[i][0]=mod.mod(res[i][0]);
            res[i][1]=mod.mod(res[i][1]);
            res[i][2]=mod.mod(res[i][2]);
        }
        return res;
    }
    auto mul_col(matrix3&b) const{
        auto res=matrix3();
        cir(k,0,3){
            res[0][0]+=(*this)[0][k]*b[k][0];
            res[0][1]+=(*this)[0][k]*b[k][1];
            res[0][2]+=(*this)[0][k]*b[k][2];
        }
        res[0][0]=mod.mod(res[0][0]);
        res[0][1]=mod.mod(res[0][1]);
        res[0][2]=mod.mod(res[0][2]);
        return res;
    }
    auto mulpow(matrix3 s,auto x,auto&upw) const{
        const auto n=(int)(this->size());
        auto cnt=0;
        while(x){
            if(x&1) s=s.mul_col(upw[cnt]);
            ++cnt;x>>=1;
        }
        return s;
    }
    matrix3(lint _v=0){
        memset(this->begin(),0,sizeof(*this));
        cir(i,0,3) (*this)[i][i]=_v; 
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T,p;inf>>T>>p;
    mod.init(p);
    const auto v=100;
    vector<vector<lint>> c(v,vector<lint>(v));
    c[0][0]=1;
    cir(i,1,v) cir(j,0,v){
        c[i][j]=c[i-1][j];
        if(j) (c[i][j]+=c[i-1][j-1])%=MOD;
    }
    vector<lint> pa(v),pb(v);
    cir(x,0,v) cir(i,0,x+1) cir(j,0,i+1) (pa[x]+=c[i][j]*i%MOD*j)%=MOD;
    cir(x,0,v) cir(i,0,x+1) cir(j,0,i+1) (pb[x]+=c[i][j]*i+c[i][j]*j)%=MOD;
    auto la=berlekamp_massey().solve(pa);
    auto lb=berlekamp_massey().solve(pb);
    la.erase(la.begin());
    lb.erase(lb.begin());
    for(auto&x:la) if(x>MOD/2) x-=MOD;
    for(auto&x:lb) if(x>MOD/2) x-=MOD;
    matrix4 ma;
    matrix3 mb;
    cir(i,0,(int)(la.size())) ma[i][0]=((-la[i])%p+p)%p;
    cir(i,0,(int)(lb.size())) mb[i][0]=((-lb[i])%p+p)%p;
    cir(i,0,(int)(la.size())-1) ma[i][i+1]=1;
    cir(i,0,(int)(lb.size())-1) mb[i][i+1]=1;
    vector<matrix4> pma;
    vector<matrix3> pmb;
    auto ua=ma;
    auto ub=mb;
    cir(i,0,65) pma.emplace_back(ua),ua=ua.mul(ua);
    cir(i,0,65) pmb.emplace_back(ub),ub=ub.mul(ub);
    matrix4 as;
    matrix3 bs,cs;
    cir(i,0,(int)(la.size())) as[0][i]=pa[la.size()-i-1]%p;
    cir(i,0,(int)(lb.size())) bs[0][i]=pb[lb.size()-i-1]%p;
    auto cnt=0;
    while(T--) [&]{
        lint n,k;inf>>n>>k;k%=p;
        if(n<v-10){
            ouf<<(pa[n]+k*pb[n]+k*k%p*(math.qpow(2,n+1,p)+p-1))%p<<'\n';
        }else{
            const auto va=(ma.mulpow(as,n-3,pma))[0][0];
            const auto vb=(mb.mulpow(bs,n-2,pmb))[0][0]*k%p;
            const auto vc=(math.qpow(2,n+1,p)+p-1)%p*k%p*k%p;
            ouf<<(va+vb+vc)%p<<'\n';
        }
    }();
    return 0;
}
