#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
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
    constexpr auto inv(lint a) const{
        return qpow(a,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<int> a(n);
    for(auto&x:a) cin>>x;
    vector<int> x(n);
    ranges::iota(x,0);
    ranges::sort(x,[&](auto x,auto y){return a[x]<a[y];});
    auto las=0;
    set<int> px;
    cir(i,0,n) px.emplace(i);
    vector f(q+1,vector(n,vector<lint>(n)));
    auto update=[&](int l,int r){
        if(r<l+2) return;
        cir(c,0,q+1) cir(i,l+1,r) cir(j,l+1,r) f[c][i][j]=0;
        f[0][l+1][r-1]=1;
        // clog<<l+1<<' '<<r-1<<'\n';  
        cir(c,1,q+1){
            auto pre=0ll;
            // clog<<"! "<<f[1][0][0]<<'\n';
            cir(pr,l+1,r) cir(pl,l+1,pr+1){
                (f[c][pl][pr]+=pre)%=MOD;
                (pre+=f[c-1][pl][pr]*pl)%=MOD;
            }
            auto suf=0ll;
            cir(pl,l+1,r) for(auto pr=r-1;pr>pl-1;--pr){
                (f[c][pl][pr]+=suf)%=MOD;
                (suf+=f[c-1][pl][pr]*max(n-pr-2,0))%=MOD;
            }
            // clog<<"??? "<<0<<' '<<0<<' '<<f[1][0][0]<<' '<<suf<<'\n';
            cir(pr,l+1,r) cir(pl,l+1,pr+1){
                (f[c][pl][pr]+=f[c-1][pl][pr]*((pl*(pl+1)/2)+((n-pr-1)*(n-pr)/2)+((pr-pl+1)*(pr-pl+2)/2)))%=MOD;
                // clog<<c<<' '<<pl<<' '<<pr<<": "<<f[c][pl][pr]<<' '<<suf<<' '<<pre<<'\n';
            }
        }
    };
    const auto c=math.qpow(n*(n+1)/2,q);
    vector<lint> ans(n);
    for(auto&w:x){
        vector<lint> pre(n+1);
        cir(i,0,n) cir(j,i,n){
            (pre[i]+=f[q][i][j])%=MOD;
            (pre[j+1]+=MOD-f[q][i][j])%=MOD;
        }
        // clog<<"??? "<<c<<' '<<pre[0]<<'\n';
        cir(i,1,n) (pre[i]+=pre[i-1])%=MOD;
        cir(i,0,n) (ans[i]+=(c+MOD-pre[i])*(a[w]-las))%=MOD;
        las=a[w];
        px.erase(w);
        const auto ux=px.lower_bound(w);
        const auto l=(ux==px.begin()?-1:*prev(ux));
        const auto r=(ux==px.end()?n:*ux);
        update(l,r);
    }
    for(auto&x:ans) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
