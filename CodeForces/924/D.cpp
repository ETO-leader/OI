#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;lint b,x;cin>>n>>b>>x;
        vector<lint> c(n);
        for(auto&i:c) cin>>i;
        auto calc=[&](lint kx){
            lint res=0;
            for(auto&i:c){
                const auto cw=i/kx;
                const auto ca=i-cw*kx;
                const auto cb=kx-ca;
                res+=i*i*b-ca*(cw+1)*(cw+1)*b-cb*cw*cw*b;
            }
            return res/2-x*(kx-1);
        };
        int l=1,r=accumulate(c.begin(),c.end(),0)+7;
        while(r-l+1>10){
            const auto lmid=l+(r-l+1)/3,rmid=l+(r-l+1)/3*2;
            const auto wl=calc(lmid),wr=calc(rmid);
            wl<wr?l=lmid:r=rmid;
        }
        lint ans=0;
        cir(i,l,r+1) ans=max(ans,calc(i));
        cout<<ans<<'\n';
    }
    return 0;
}
