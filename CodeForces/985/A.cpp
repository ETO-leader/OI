#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int l,r,k;cin>>l>>r>>k;
        if(1ll*l*k>r) println("{}",0);
        else println("{}",r/k-l+1);
    }();
    return 0;
}
