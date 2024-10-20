#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    map<char,int> cnt;
    for(auto&i:s) ++cnt[i];
    auto ans=0ll;
    map<char,int> acnt;
    for(auto&i:s){
        for(auto&[c,b]:acnt) ans+=1ll*b*(cnt[c]-b-(i==c));
        ++acnt[i];
    }
    cout<<ans<<'\n';
    return 0;
}
