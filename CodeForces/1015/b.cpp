#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        ranges::sort(a);
        const auto w=a[0];
        auto gx=0ll;
        a.erase(a.begin());
        for(auto&i:a) if(!(i%w)) gx=gcd(gx,i);
        cout<<(gx==w?"Yes":"No")<<'\n';
    }();
    return 0;
}
