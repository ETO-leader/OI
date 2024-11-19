#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;string a,b;cin>>a>>b;
        const auto ax=[&](){
            auto cnta=0;
            cir(i,0,n) cnta+=a[i]!=b[i];
            return cnta*2-(cnta&1);
        }();
        const auto bx=[&](){
            auto cnta=0;
            ranges::reverse(b);
            cir(i,0,n) cnta+=a[i]!=b[i];
            return max(cnta*2-(!(cnta&1)),2);
        }();
        println("{}",min(ax,bx));
    }();
    return 0;
}
