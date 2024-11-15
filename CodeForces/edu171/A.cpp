#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int x,y,k;cin>>x>>y>>k;
        x=y=min(x,y);
        println("{} {} {} {}",0,0,x,x);
        println("{} {} {} {}",0,x,x,0);
    }();
    return 0;
}
