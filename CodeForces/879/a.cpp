#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        const auto nc=ranges::count(a,-1);
        const auto nnc=ranges::count(a,1);
        auto ans=max<int>(0,(nc-nnc+1)/2);
        ans+=(nc-ans)&1;
        println("{}",ans);
    }();
    return 0;
}
