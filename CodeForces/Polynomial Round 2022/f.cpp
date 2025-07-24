#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
static constexpr auto inv2=(MOD+1)/2;
static constexpr auto _infl=(lint)(1e16l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n;cin>>n;
        vector<pair<lint,lint>> info(n);
        for(auto&[op,x]:info){
            cin>>op;
            if(op<3) cin>>x;
        }
        vector<lint> pval(n);
        auto uval=0ll;
        cir(i,0,n){
            if(info[i].first==3){
                pval[i]=uval;
                uval*=2;
            }else if(info[i].first==2){
                uval+=info[i].second;
            }
            uval=min(uval,_infl);
        }
        vector<lint> vlx;
        auto pw=1ll,ipw=1ll;
        for(auto p=0;p<n&&info[p].first!=2;++p){
            if(info[p].first==3) (pw*=2)%=MOD,(ipw*=inv2)%=MOD;
            vlx.emplace_back(ipw);
        }
        cir(i,0,n) vlx.emplace_back(ipw);
        set<lint,greater<>> vals;
        auto ans=0ll,suf=0ll;
        for(auto i=n-1;~i;--i){
            if(info[i].first==3){
                if(pval[i]) vals.emplace(pval[i]);
            }else if(info[i].first==2){
                suf+=info[i].second;
            }else{
                auto w=info[i].second-suf;
                if(w<1) continue;
                for(auto siz=(int)(vals.size());auto&x:vals){
                    if(w>x){
                        (ans+=(1ll<<(siz-1))*vlx[i])%=MOD;
                        w-=x;
                    }
                    --siz;
                }
                (ans+=vlx[i])%=MOD;
            }
        }
        cout<<(ans*pw)%MOD<<'\n';
    }();
    return 0;
}
