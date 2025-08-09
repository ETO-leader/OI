#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        vector<lint> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        auto ans=0ll;
        cir(i,0,n) ans+=abs(a[i]-b[i]);
        vector<pair<lint,lint>> l(n);
        cir(i,0,n) l[i]=pair(min(a[i],b[i]),max(a[i],b[i]));
        ranges::sort(l);
        auto mxr=-1ll,mn=(lint)(1e18l);
        cir(i,0,n){
            if(i){
                mn=min(mn,max<lint>((l[i].first-mxr)*2,0));
            }
            mxr=max(mxr,l[i].second);
        }
        cout<<ans+mn<<'\n';
    }();
    return 0;
}
