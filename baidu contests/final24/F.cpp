#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(int x){return x&(-x);}
public:
    auto update(int u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) (a[u]+=w)%=MOD;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) (res+=a[u]);
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    map<int,int> id;
    for(auto&i:a) id.emplace(i,0);
    auto ix=-1;
    for(auto&[x,y]:id) y=++ix;
    for(auto&i:a) i=id[i];
    vector<lint> lf(n);
    bit bx(id.size()+7);
    cir(i,0,n){
        lf[i]=(bx.query(a[i]-1)+1)%MOD;
        bx.update(a[i],lf[i]);
    }
    vector<lint> rg(n);
    bit by(id.size()+7);
    for(auto i=n-1;~i;--i){
        rg[i]=(by.query(a[i]-1)+1)%MOD;
        by.update(a[i],rg[i]);
    }
    auto ans=0ll;
    cir(i,0,n) (ans+=lf[i]*rg[i])%=MOD;
    cout<<ans<<'\n';
    return 0;
}
