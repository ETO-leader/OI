#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        if(n==1) return cout<<a[0]<<'\n',void();
        const auto aw=a.back();a.pop_back();
        const auto mw=a.back();a.pop_back();
        cout<<accumulate(a.begin(),a.end(),0ll)+aw-mw<<'\n';
    }();
    return 0;
}
