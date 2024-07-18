#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ans=numeric_limits<int>::max();
        cir(i,1,n) ans=min(ans,max(a[i-1],a[i]));
        cout<<ans-1<<'\n';
    }();
    return 0;
}
