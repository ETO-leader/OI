#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<lint> a(n),b(m);
        for(auto&x:a) cin>>x;
        for(auto&x:b) cin>>x;
        auto w=b.back();b.pop_back();
        ranges::sort(a);
        ranges::sort(b,greater<>());
        b.emplace(b.begin(),w);
        auto cur=accumulate(a.begin(),a.end(),0ll);
        auto ans=-1ll;
        cir(i,0,min(n,m)){
            cur+=b[i]-a[i];
            ans=max(ans,cur);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
