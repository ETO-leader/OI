#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("dsa.in");
ofstream ouf("dsa.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=unsigned long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    unordered_map<lint,vector<lint>> uwn;
    unordered_map<lint,vector<int>> urev;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    auto rev(const auto n){
        if(urev.count(n)) return&urev[n];
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        urev[n]=rev;
        return&urev[n];
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto wn(const auto h){
        if(uwn.count(h)) return&uwn[h];
        const auto wx=qpow(omega,(MOD-1)/h);
        vector<lint> xwn(h);
        auto u=1ll;
        for(auto&x:xwn) x=u,(u*=wx)%=MOD;
        uwn[h]=xwn;
        return&uwn[h];
    }
} math;
class poly:public vector<lint>{
public:
    using vector<lint>::vector;
    auto change(poly&a,const auto n){
        auto rev=math.rev(n);
        cir(i,0,n) if(i<(*rev)[i]) std::swap(a[i],a[(*rev)[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const auto n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            auto wn=math.wn(h);
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*(*wn)[k-i]%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=a[k+midh]>MOD-1?MOD:0;
                    a[k]+=wk;
                    a[k]-=a[k]>MOD-1?MOD:0;
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
    auto transform(const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        if(size()!=nlen) resize(nlen);
        ntt<1>(*this,nlen);
    }
    auto itransform(const auto req_len){
        const auto nlen=1<<(int)(ceil(log2(req_len)));
        if(size()!=nlen) resize(nlen);
        ntt<-1>(*this,nlen);
    }
    auto transform(){transform(size());}
    auto itransform(){itransform(size());}
    friend auto operator*(poly a,poly b){
        const auto nlen=1<<(int)(ceil(log2(a.size()+b.size())));
        a.transform(nlen);b.transform(nlen);
        cir(i,0,nlen) (a[i]*=b[i])%=MOD;
        a.itransform();
        return a;
    }
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;vector<int> a(n);
    for(auto&i:a) inf>>i;
    if(*max_element(a.begin(),a.end())>1){
        const auto suma=accumulate(a.begin(),a.end(),0);
        vector<vector<vector<lint>>> f(1<<n,vector<vector<lint>>(suma*2+7,vector<lint>(n+1)));
        f[0][suma][0]=1;
        cir(s,0,(1<<n)) for(auto c=suma*2+3;~c;--c) cir(ck,0,n+1) if(f[s][c][ck]){
            // Type 1: choose new number
            unordered_set<int> aps;
            cir(i,0,n) if(!(s&(1<<i))){
                if(aps.count(a[i])) continue;
                aps.emplace(a[i]);
                (f[s|(1<<i)][c+a[i]][ck+(c+a[i]==suma)]+=f[s][c][ck])%=MOD;
            }
            // Type 2: choose -1
            if(c) (f[s][c-1][ck+(c-1==suma)]+=f[s][c][ck])%=MOD;
        }
        cir(k,1,n+1) ouf<<f[(1<<n)-1][suma][k]<<'\n';
    }else{
        vector<vector<lint>> g(n*2+1,vector<lint>(n*2+1));
        g[1][1]=1;
        cir(i,1,n*2) cir(j,1,n*2){
            (g[i+1][j+1]+=g[i][j])%=MOD;
            (g[i+1][j-1]+=g[i][j])%=MOD;
        }
        poly f{1},x(n+1);
        cir(i,0,n*2+1) (x[i/2]+=g[i][0]*2)%=MOD;
        x.transform(n*2+1);
        cir(i,0,n){
            f.transform(n*2+1);
            cir(i,0,(int)(f.size())) (f[i]*=x[i])%=MOD;
            f.itransform();
            ouf<<f[n]<<'\n';
        }
    }
    return 0;
}
