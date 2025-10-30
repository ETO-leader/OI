#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int64_t n;cin>>n;
        auto ans=(int64_t)(11);
        auto p=1ll;
        cir(len,2,19){
            p*=10;
            if(n<p) break;
            cir(b,1,10) if((!(len%b))&&(b<len)){
                auto l=(int64_t)(1),r=(int64_t)(1),uans=(int64_t)(-1);
                cir(i,0,b-1) l*=10;
                cir(i,0,b) r*=10;
                --r;
                const auto k=(r+1);
                while(l<r+1){
                    const auto mid=midpoint(l,r);
                    auto w=(int64_t)(0);
                    cir(i,0,len/b){
                        w=min<__int128_t>((__int128_t)(w)*k+mid,2e18l);
                    }
                    w<n+1?((l=mid+1),(uans=w)):(r=mid-1);
                }
                ans=max(ans,uans);
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
