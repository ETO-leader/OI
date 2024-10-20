#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,k;cin>>n>>k;
        if(k==1) return println("{}",n);
        auto ans=0;
        while(n) ans+=n%k,n/=k;
        println("{}",ans);
    }();
    return 0;
}
