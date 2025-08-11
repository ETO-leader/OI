#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;lint s;cin>>n>>s;
    lint l,r;cin>>l>>r;
    auto rg=pair(s,s);
    map<lint,lint> op;
    cir(i,0,n){
        int t,x;cin>>t>>x;op[t]+=x;
    }
    auto ans=0;
    for(auto&[a,b]:op){
        rg.first+=b;rg.second+=b;
        if(rg.second<l||r<rg.first) ++ans,rg=pair(l,r);
    }
    cout<<ans<<'\n';
    return 0;
}
