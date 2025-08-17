#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n;int m;cin>>n>>m;
    const auto sg=[&](lint len,int l,int r){
        if(((!l)&&(!r))||((l==1)&&(r==1))) return (lint)(len>0);
        if(((!l)&&(r==1))||((l==1)&&(!r))) return 0ll;
        if(l==2&&r==2) return len&1;
        return len;
    };
    vector<pair<lint,int>> pos(m);
    for(auto&[a,b]:pos) cin>>a>>b;
    pos.emplace(pos.begin(),0,2);
    pos.emplace_back(n+1,2);
    auto ok=0ll;
    cir(i,1,m+2) ok^=sg(pos[i].first-pos[i-1].first-1,pos[i-1].second,pos[i].second);
    cout<<(ok?"Takahashi":"Aoki")<<'\n';
    return 0;
}
