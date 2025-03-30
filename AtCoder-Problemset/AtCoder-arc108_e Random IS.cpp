#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) (a[u]+=w)%=MOD;
    }
    auto query(int u) const{
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) (res+=a[u])%=MOD;
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    const auto maxa=*ranges::max_element(a)+7;
    a.insert(a.begin(),0);
    a.emplace_back(maxa-1);
    n+=2;
    vector f(n,vector<lint>(n));
    vector pre(n,bit(maxa+1)),suf(n,bit(maxa+1)),cnt(n,bit(maxa+1));
    cir(len,2,n+1) cir(l,0,n-len+1){
        const auto r=l+len-1;
        if(a[l]>a[r]) continue;
        const auto c=cnt[l].query(a[r])-cnt[l].query(a[l]-1);
        if(c) f[l][r]=(((suf[l].query(a[r])+MOD-suf[l].query(a[l]-1))+(pre[r].query(a[r])+MOD-pre[r].query(a[l]-1)))*math.inv(c)+1)%MOD;
        cnt[l].update(a[r],1);
        suf[l].update(a[r],f[l][r]);
        pre[r].update(a[l],f[l][r]);
    }
    cout<<f[0][n-1]<<'\n';
    return 0;
}
