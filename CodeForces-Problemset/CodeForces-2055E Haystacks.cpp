#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<lint> a(n),b(n);
        cir(i,0,n) cin>>a[i]>>b[i];
        vector<int> ord(n);
        ranges::iota(ord,0);
        ranges::sort(ord,[&](auto i,auto j){
            if(a[i]-b[i]<1&&a[j]-b[j]>0) return true;
            if(a[i]-b[i]>0&&a[j]-b[j]<1) return false;
            return a[i]-b[i]<1?a[i]<a[j]:b[i]>b[j];
        });
        const auto sum=[&]{
            auto res=0ll;
            cir(i,0,n) res+=b[i]-a[i];
            return res;
        }();
        [&]{
            const auto ax=a,bx=b;
            cir(i,0,n) a[i]=ax[ord[i]],b[i]=bx[ord[i]];
        }();
        vector<int> vaild;
        cir(i,0,n) if(b[i]<sum+1) vaild.emplace_back(i);
        if(vaild.empty()) return println("-1");
        vector<lint> w(n),pm(n),sm(n);
        cir(i,0,n) w[i]=a[i]-(i?b[i-1]-w[i-1]:0);
        cir(i,0,n) pm[i]=max((i?pm[i-1]:-_infl),w[i]);
        for(auto i=n-1;~i;--i) sm[i]=max((i+1<n?sm[i+1]:-_infl),w[i]);
        auto ans=_infl;
        const auto suma=accumulate(a.begin(),a.end(),0ll);
        for(auto&i:vaild) ans=min(ans,suma+max((i?pm[i-1]:-_infl),(i+1<n?sm[i+1]-a[i]+b[i]:-_infl)));
        println("{}",ans);
    }();
    return 0;
}
