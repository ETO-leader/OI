#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr auto lowbit(int x){return x&(-x);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int x,y;cin>>x>>y;
        cout<<lowbit(x^y)<<'\n';
    }();
    return 0;
}
