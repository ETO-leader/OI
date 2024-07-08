#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e8+7;
static constexpr auto qpow(lint a,lint b){
    assert(b>-1);
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
static constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
vector<VI> chs;
VI wx;
auto add(int u,lint w,lint a)->void{
    (wx[u]+=w)%=MOD;(w*=a)%=MOD;
    for(auto&i:chs[u]) add(i,w,a);
}
int main(){
    //ios::sync_with_stdio(false),cin.tie(0);
    int n,q,a;cin>>n>>q>>a;chs.resize(n+1);
    wx.resize(n+1);
    cir(i,2,n+1){
        int f;cin>>f;
        chs[f].push_back(i);
    }
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u,x;cin>>u>>x;
            add(u,(x<0?qpow(inv(a),-x):qpow(a,x)),a);
        }else{
            int u;cin>>u;
            cout<<(wx[u]+MOD)%MOD<<'\n';
        }
    }
    return 0;
}
