#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto l=0ll,r=_infl,ans=-1ll;
        while(l-1<r){
            const auto mid=midpoint(l,r);
            [&](){
                auto cnt=0ll;
                for(auto&i:a) cnt+=mid/i+1;
                return cnt<mid+1;
            }()?((r=mid-1),(ans=mid)):(l=mid+1);
        }
        if(ans<0) return cout<<ans<<'\n',void();
        vector<lint> ansx(n);
        cir(i,0,n-1) ansx[i]=ans/a[i]+1;
        ansx[n-1]=ans-accumulate(ansx.begin(),ansx.end()-1,0ll);
        cir(i,0,n) assert(ansx[i]*a[i]>ans);
        for(auto&i:ansx) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
