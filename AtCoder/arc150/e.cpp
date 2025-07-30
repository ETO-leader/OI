#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n,k;cin>>n>>k;
    string str;cin>>str;
    vector<int> a(n);
    cir(i,0,n) a[i]=(str[i]=='L'?-1:1);
    if(accumulate(a.begin(),a.end(),0)<0){
        for(auto&i:a) i*=-1;
        ranges::reverse(a);
    }
    auto s=a;
    cir(i,1,n) s[i]+=s[i-1];
    if(!s[n-1]){
        auto ans=0ll;
        cir(i,0,n) (ans+=(s[i]>(a[i]==1?0:-1)));
        cout<<ans*k%MOD<<'\n';
    }else{
        auto ans=0ll;
        const auto sk=s[n-1]*k;
        auto pok=false;
        cir(i,0,n){
            if(s[i]>0) pok=true;
            (ans+=(a[i]==1?max<lint>(k-max<lint>((sk-s[i])/s[n-1]+1,0),0)*2:(k-(!pok))))%=MOD;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
