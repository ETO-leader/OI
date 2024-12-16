#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        auto maxw=0,maxr=0;
        cir(i,0,m){
            int r,w;cin>>r>>w;
            maxr=max(maxr,r);
            maxw=max(maxw,w);
        }
        if(maxr+maxw>n) return println("IMPOSSIBLE");
        println("{}",string(maxr,'R')+string(n-maxr,'W'));
    }();
    return 0;
}
