#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto g=0;
        for(auto&i:a) g=gcd(g,i);
        for(auto&i:a) i/=g;
        ranges::sort(a);
        auto nw=a[0],ans=a[0];
        auto cnt=n-1;
        a.erase(a.begin());
        while(nw>1){
            --cnt;
            auto mg=nw;
            for(auto&i:a){
                mg=min(mg,gcd(i,nw));
            }
            ans+=(nw=mg);
        }
        cout<<(ans+cnt)*g<<'\n';
    }();
    return 0;
}
