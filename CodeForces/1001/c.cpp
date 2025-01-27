#include<bits/stdc++.h>
#define int long long
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int32_t main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ans=accumulate(a.begin(),a.end(),0ll);
        while(n>1){
            vector<int> ax(n);
            cir(i,0,n-1) ax[i]=a[i+1]-a[i];
            a=ax;--n;
            ans=max(ans,abs(accumulate(a.begin(),a.end(),0ll)));
        }
        println("{}",ans);
    }();
    return 0;
}
