#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("tour.in");
ofstream ouf("tour.out");
#else
auto&inf(cin);
auto&ouf(cout);
#endif
using lint=unsigned long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
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
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    constexpr auto C(auto a,auto b) const{
        return (a>b-1&&b>-1)?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int ty;inf>>ty;
    int n,m,k;inf>>n>>m>>k;
    math.init(n+m+7);
    vector<pair<int,int>> a(k);
    for(auto&[x,y]:a) inf>>x>>y;
    a.emplace_back(1,2);
    a.emplace_back(2,1);
    a.emplace_back(n-1,m);
    a.emplace_back(n,m-1);
    a.emplace_back(n,m);
    sort(a.begin(),a.end(),[&](auto&a,auto&b){
        return a.first+a.second==b.first+b.second?a.first<b.first:a.first+a.second<b.first+b.second;
    });
    for(auto&[x,y]:a) --x,--y;
    vector<vector<lint>> uc(k+7,vector<lint>(k+7));
    cir(i,0,k+5) cir(j,0,i){
        uc[i][j]=math.C(a[i].first-a[j].first+a[i].second-a[j].second,a[i].first-a[j].first);
    }
    vector<vector<lint>> f(k+5,vector<lint>(k+5));
    if(ty&1){
        f[1][0]=1;
        cir(i,0,k+4) cir(j,0,i+1){
            const auto stpx=uc[i+1][i];
            const auto stpy=uc[i+1][j];
            (f[i+1][j]+=f[i][j]*stpx)%=MOD;
            (f[i+1][i]+=f[i][j]*stpy)%=MOD;
            (f[i+1][i+1]+=MOD-f[i][j]*stpx%MOD*stpy%MOD)%=MOD;
            // clog<<i<<' '<<j<<": "<<f[i][j]<<'\n';
        }
        ouf<<f[k+4][k+4]<<'\n';
    }
    if(ty&2){
        for(auto&x:f) fill(x.begin(),x.end(),0);
        f[0][1]=1;
        cir(i,1,k+3) cir(j,0,i){
            const auto stpx=uc[i+1][i];
            const auto stpy=uc[i+1][j];
            (f[i][i+1]+=f[i][j]*stpy)%=MOD;
            (f[i+1][j]+=f[i][j]*stpx)%=MOD;
            (f[i+1][i]+=f[j][i]*stpy)%=MOD;
            (f[j][i+1]+=f[j][i]*stpx)%=MOD;
        }
        ouf<<(f[k+2][k+3]+MOD-f[k+3][k+2])*2%MOD<<'\n';
    }
    return 0;
}

