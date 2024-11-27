#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("rand.in");
ofstream fcout("rand.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using poly=vector<lint>;
static constexpr auto omega=3;
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
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
} math;
auto operator*(poly a,poly b){
    if(a.size()<b.size()) swap(a,b);
    auto res=poly(a.size()+b.size());
    cir(i,0,(int)(a.size())){
        auto p=0;
        for(;p+4<(int)(b.size());p+=4){
            (res[i+p]+=a[i]*b[p])%=MOD;
            (res[i+p+1]+=a[i]*b[p+1])%=MOD;
            (res[i+p+2]+=a[i]*b[p+2])%=MOD;
            (res[i+p+3]+=a[i]*b[p+3])%=MOD;
        }
        for(;p<(int)(b.size());++p) (res[i+p]+=a[i]*b[p])%=MOD;
    }
    while(!res.back()) res.pop_back();
    return res;
}
auto operator/(poly a,poly b){
    while(!a.back()) a.pop_back();
    while(!b.back()) b.pop_back();
    poly ans;
    const auto ivb=math.inv(b.back());
    for(auto i=(int)(a.size())-1;i>(int)(b.size())-2;--i){
        const auto w=a[i]*ivb%MOD;
        cir(x,0,(int)(b.size())) (a[i-x]+=MOD-w*b[(int)(b.size())-x-1]%MOD)%=MOD;
        ans.push_back(w);
    }
    reverse(ans.begin(),ans.end());
    while(!ans.back()) ans.pop_back();
    return ans;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,m;fcin>>n>>m;
    const auto invprob=math.inv(m);
    vector<lint> cur(n,1);
    map<int,vector<int>> pw;
    cir(i,0,n) cir(j,0,m){
        int x;fcin>>x;pw[x].push_back(i);
    }
    auto curp=poly{1};
    cir(i,0,n) curp=curp*poly{1,0};
    vector<pair<lint,int>> ans;
    auto cnt=0;
    for(auto&[w,x]:pw){
        auto pre=0ll;
        cir(i,0,min<int>(curp.size(),n/2+1)) (pre+=curp[i]);
        ans.emplace_back(pre,w);
        for(auto&i:x){
            curp=curp/poly{cur[i],(MOD+1-cur[i])%MOD};
            (cur[i]+=MOD-invprob)%=MOD;
            curp=curp*poly{cur[i],(MOD+1-cur[i])%MOD};
        }
    }
    cir(i,1,(int)(ans.size())) (ans[i-1].first+=MOD-ans[i].first)%=MOD;
    auto answ=0ll;
    for(auto&[p,w]:ans) (answ+=p*w)%=MOD;
    fcout<<answ<<'\n';
    return 0;
}
