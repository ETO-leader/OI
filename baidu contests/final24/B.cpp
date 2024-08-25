#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using bnum=bitset<2007>;
auto sum(bnum a,bnum b)->bnum{
    return (a&b).count()?sum((a&b)<<1,a^b):a|b;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;
    auto w=bnum(s),k=bnum(s);
    cir(i,0,20) w=sum(w,k);
    auto p=2000;
    while(!w[p]) --p;
    for(;~p;--p) cout<<w[p];
    cout<<'\n';
    return 0;
}
