#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,x,y;cin>>n>>x>>y;
        const auto s=min(x,y);
        cout<<(n+s-1)/s<<'\n';
    }();
    return 0;
}
