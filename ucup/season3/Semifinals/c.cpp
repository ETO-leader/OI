#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
constexpr auto abs128(auto x){
    return x<0?-x:x;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k;cin>>n>>k;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto l=(lint)(-1e16l),r=(lint)(1e16l);
        auto ans=false;
        while(l-1<r){
            const auto mid=(l+r)/2;
            auto val=(__int128_t)(a[0])*(-k);
            const auto ok=[&]{
                auto sgn=1;
                cir(i,1,n){
                    sgn*=-1;
                    (val+=a[i])-=mid;
                    if(abs128(val)>1e25) return val*sgn>0;
                    val*=-k;
                }
                if(!val) ans=true;
                return val*sgn>0;
            }();
            ok?(l=mid+1):(r=mid-1);
            // clog<<l<<' '<<r<<'\n';
        }
        // clog<<l<<' '<<r<<'\n';
        cout<<(ans?"Yes":"No")<<'\n';
    }();
    return 0;
}
