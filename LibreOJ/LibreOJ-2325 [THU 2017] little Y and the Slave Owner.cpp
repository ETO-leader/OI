#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using uqint=__uint128_t;
static constexpr auto MOD=998244353;
class matrix{
private:
    vector<vector<uqint>> a;
    int n,m;
public:
    auto&operator[](size_t p){return a[p];}
    auto operator*(matrix x) const{
        auto res=matrix(n,x.m);
        cir(k,0,m) cir(i,0,n) cir(j,0,x.m){
            res[i][j]+=a[i][k]*x[k][j];
        }
        for(auto&i:res.a) for(auto&w:i) w%=MOD;
        return res;
    }
    matrix(int _n,int _m):n(_n),
        m(_m),a(_n,vector<uqint>(_m)){}
    matrix()=default;
};
class basic_math{
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
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T,m,k;cin>>T>>m>>k;
    map<vector<int>,int> stid;
    [&](){
        auto c=0;
        cir(i,0,k+1) cir(j,0,k+1) cir(x,0,k+1){
            if(m<3&&x) continue;
            if(m<2&&j) continue;
            if(i+j+x>k) continue;
            stid[{i,j,x}]=c++;
        }
    }();
    const auto pwidth=(int)(stid.size());
    matrix fx(pwidth+1,pwidth+1);
    fx[pwidth][pwidth]=1;
    for(auto&[s,id]:stid){
        const auto c=s[0]+s[1]+s[2];
        const auto p=math.inv(c+1);
        auto ns=s;
        // chs Boss
        [&](){
            (fx[id][id]+=p)%=MOD;
            (fx[id][pwidth]+=p)%=MOD;
        }();
        // chs 0
        if(m>0) [&](){
            --ns[0];
            if(stid.count(ns)) (fx[id][stid[ns]]+=p*s[0])%=MOD;
            ++ns[0];
        }();
        // chs 1
        if(m>1) [&](){
            --ns[1];++ns[0];if(c<k) ++ns[m-1];
            if(stid.count(ns)) (fx[id][stid[ns]]+=p*s[1])%=MOD;
            ++ns[1];--ns[0];if(c<k) --ns[m-1];
        }();
        // chs 2
        if(m>2) [&](){
            --ns[2];++ns[1];if(c<k) ++ns[2];
            if(stid.count(ns)) (fx[id][stid[ns]]+=p*s[2])%=MOD;
            ++ns[2];--ns[1];if(c<k) --ns[2];
        }();
    }
    vector<matrix> pw(63);
    cir(i,0,63){
        pw[i]=fx;fx=fx*fx;
    }
    while(T--) [&](){
        lint n;cin>>n;
        matrix ans(1,pwidth+1);ans[0][stid[{m==1,m==2,m==3}]]=1;
        cir(i,0,63) if((n>>i)&1) ans=ans*pw[i];
        cout<<(lint)(ans[0][pwidth])<<'\n';
    }();
    return 0;
}
