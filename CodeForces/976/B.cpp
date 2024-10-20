#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        lint k;cin>>k;
        auto check=[&](lint x){
            return x-(lint)(sqrtl(x));
        };
        auto l=0ll,r=(lint)(3e18l),ans=-1ll;
        while(l-1<r){
            const auto mid=midpoint(l,r);
            check(mid)<k?(l=mid+1):((r=mid-1),(ans=mid));
        }
        println("{}",ans);
    }();
    return 0;
}
