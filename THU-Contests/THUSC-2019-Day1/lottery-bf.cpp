#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<int> fct;
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto a){
        return qpow(a,MOD-2);
    }
} math;
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(auto u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) (a[u]+=w)%=MOD;
    }
    auto query(auto u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) (res+=a[u])%=MOD;
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<lint> cur(n),rest(n);
    cir(i,0,n){
        int a,b;cin>>a>>b;cur[i]=a+b;rest[i]=a;
    }
    bit bx(n),pre(n);
    cir(i,0,n) bx.update(i,rest[i]),pre.update(i,rest[i]);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,c;cin>>l>>r>>c;--l;--r;
            cir(i,l,r+1){
                const auto lrest=rest[i];
                (rest[i]*=(max(cur[i]-c,0ll)*math.inv(cur[i]%MOD)%MOD))%=MOD;
                bx.update(i,(rest[i]+MOD-lrest)%MOD);
                cur[i]=max(cur[i]-c,0ll);
            }
        }else if(op==2){
            int l,r;cin>>l>>r;--l;--r;
            const auto ans=
                ((pre.query(r)+MOD-(l?pre.query(l-1):0))%MOD+MOD-
                (bx.query(r)+MOD-(l?bx.query(l-1):0))%MOD)%MOD;
            cout<<ans<<'\n';
        }else{
            int p,a,b;cin>>p>>a>>b;--p;
            clog<<rest[p]<<'\n';
            cur[p]+=a+b;
            (rest[p]+=a)%=MOD;
            bx.update(p,a);
            pre.update(p,a);
            // clog<<rest[p]<<' '<<cur[p]<<'\n';
        }
    }
    return 0;
}