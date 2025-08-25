#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxv=(int)(2e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    // int T;cin>>T;
    auto T=1;
    while(T--) [&]{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        cir(i,0,n) a.emplace_back(0);
        n*=2;
        bitset<maxv> f;f.reset();
        f.set(1);
        auto ans=0ll,pre=0ll;
        const auto sa=accumulate(a.begin(),a.end(),0ll);
        cir(i,0,n){
            pre+=a[i];
            f>>=1;
            if(f.test(0)) ans=max(ans,pre-i);
            f|=(f<<a[i]);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
