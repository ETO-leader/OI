#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<lint> h(n),a(n),rx(n),ar(n);
        for(auto&i:h) cin>>i;
        for(auto&i:a) cin>>i;
        for(auto&i:rx) cin>>i;
        iota(ar.begin(),ar.end(),0);
        sort(ar.begin(),ar.end(),[&](
            int a,int b){return rx[a]>rx[b];});
        if(n>2&&n<51){
            cir(i,0,n) h[i]-=a[i];
            cir(d,0,1e4+7) if([&](){
                cir(i,0,n) h[i]+=a[i];
                cir(i,1,n) if(h[ar[i]]<h[ar[i-1]]+1)
                    return false;
                return cout<<d<<'\n',true;
            }()) return;
            return cout<<"-1\n",void();
        }
        auto l=(lint)(0),r=_inf;
        cir(i,1,n){
            auto lp=ar[i-1],p=ar[i];
            if(h[p]<h[lp]+1&&a[p]<a[lp]+1)
                return cout<<"-1\n",void();
            if(h[p]>h[lp]-1&&a[p]>a[lp]-1)
                continue;
            if(h[p]<h[lp]+1){
                const auto nl=(h[lp]-h[p]
                    )/(a[p]-a[lp])+1;
                l=max(l,nl);
            }else if(a[lp]-a[p]){
                const auto nr=(h[p]-h[lp]
                    )/(a[lp]-a[p])+1;
                r=min(r,nr);
            }
        }
        cout<<(l>r?-1:l)<<'\n';
    }();
    return 0;
}
