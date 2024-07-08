#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        lint a,b;cin>>a>>b;
        auto gx=gcd(a,b);
        a/=gx;b/=gx;
        if(a>b) swap(a,b);
        cout<<(a==1?b*b:a*b)*gx<<'\n';
    }();
    return 0;
}