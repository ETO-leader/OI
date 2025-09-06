#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("rain.in");
ofstream ouf("rain.out");
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
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
class matrix:public vector<vector<lint>>{
public:
    auto operator*(const matrix a){
        const auto n=(int)(this->size());
        auto res=matrix(n);
        cir(k,0,n) cir(i,0,n) cir(j,0,n) (res[i][j]+=(*this)[i][k]*a[k][j])%=MOD;
        return res;
    }
    auto pow(auto b){
        const auto n=(int)(this->size());
        auto res=matrix(n,1),pw=*this;
        while(b){
            if(b&1) res=res*pw;
            pw=pw*pw;b>>=1;
        }
        return res;
    }
    matrix(int _n,lint _v=0){
        this->resize(_n,vector<lint>(_n));
        cir(i,0,_n) (*this)[i][i]=_v;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int k,l,r;inf>>k>>l>>r;
    string s;inf>>s;
    vector<vector<vector<lint>>> f(r-l+2,vector<vector<lint>>(k,vector<lint>(k)));
    cir(i,0,k) f[0][i][i]=1;
    const auto ivk=math.inv(k);
    cir(t,0,r-l+1) cir(s,0,k) cir(i,0,k){
        (f[t+1][s][0]+=(f[t][s][i]*(i+1)%MOD*ivk))%=MOD;
        if(i<k-1) (f[t+1][s][i+1]+=f[t][s][i]*(k-i-1)%MOD*ivk)%=MOD;
    }
    matrix xf(k);
    cir(i,0,k){
        (xf[i][0]+=(i+1)*ivk)%=MOD;
        if(i<k-1) (xf[i][i+1]+=(k-i-1)*ivk)%=MOD;
    }
    const auto zs=xf.pow(l);
    map<pair<int,int>,vector<lint>> uf;
    map<pair<int,int>,int> lt;
    auto x=0,y=0;
    auto ans=1ll;
    cir(i,l,r+1){
        if(i-l){
            const auto c=s[i-l-1];
            if(c=='U') --x;
            else if(c=='D') ++x;
            else if(c=='L') --y;
            else ++y;
        }
        if(uf.count({x,y})){
            vector<lint> uw(k+1);
            const auto lf=uf[{x,y}];
            const auto ut=i-lt[{x,y}];
            cir(a,0,k) cir(b,0,k) (uw[b]+=lf[a]*f[ut][a][b])%=MOD;
            auto cnt=0ll;
            cir(b,1,k) (cnt+=uw[b])%=MOD;
            (ans*=cnt)%=MOD;
            auto s=accumulate(uw.begin(),uw.end(),0ll)%MOD;
            const auto w=math.inv(s+MOD-uw[0]);
            uw[0]=0;
            for(auto&x:uw) (x*=w)%=MOD;
            lt[{x,y}]=i;
            uf[{x,y}]=uw;
        }else{    
            vector<lint> uw(k+1);
            auto lf=zs[0];
            const auto ut=i-l;
            cir(a,0,k) cir(b,0,k) (uw[b]+=lf[a]*f[ut][a][b])%=MOD;
            auto cnt=0ll;
            cir(b,1,k) (cnt+=uw[b])%=MOD;
            (ans*=cnt)%=MOD;
            auto s=accumulate(uw.begin(),uw.end(),0ll)%MOD;
            const auto w=math.inv(s+MOD-uw[0]);
            uw[0]=0;
            for(auto&x:uw) (x*=w)%=MOD;
            lt[{x,y}]=i;
            uf[{x,y}]=uw;
        }
    }
    ouf<<ans<<'\n';
    return 0;
}
