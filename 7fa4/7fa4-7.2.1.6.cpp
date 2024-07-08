#include<bits/stdc++.h>
#define cir(i,a,b) for(lint i=a;i<b;++i)
using namespace std;
using lint=long long;
auto bsgs(lint n,lint l,lint r,lint a,lint b,lint p){
    vector<lint> modp;--n;
    const auto sqr=(lint)(sqrtl(n))+7;
    auto ans=0ll;b+=a;
    cir(i,0,sqr){
        if(i>n) return ans;
        const auto w=((a*i)+b)%p;
        ans+=(l-1<w&&w-1<r);
        modp.push_back(w);
    }
    sort(modp.begin(),modp.end());
    auto sum=[&](lint l,lint r){
        return upper_bound(modp.begin(),modp.end(),r)
            -upper_bound(modp.begin(),modp.end(),l-1);
    };
    auto sw=sqr;
    for(;sw+sqr<n+1;sw+=sqr){
        const auto wi=(lint)((__int128_t)(a)*sw%p);
        const auto adtl=(l+p-wi)%p;
        const auto adtr=(r+p-wi)%p;
        assert((wi+adtl)%p==l);
        assert((wi+adtr)%p==r);
        if(adtl<adtr+1){
            ans+=sum(adtl,adtr);
        }else{
            ans+=sum(0,adtr)+sum(adtl,p-1);
        }
    }
    cir(i,sw,n+1){
        const auto w=(lint)(((__int128_t)(a)*i+b)%p);
        ans+=(l-1<w&&w-1<r);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint a,b,n,l,r,p;cin>>a>>b>>n>>l>>r>>p;
    cout<<bsgs(n,l,r,a,b,p)<<'\n';
    return 0;
}
