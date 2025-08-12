#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<pair<int,int>> es(n);
    for(auto&[l,r]:es) cin>>l>>r;
    auto p=-1,ans=0;
    while(true){
        auto np=_inf;
        for(auto&[l,r]:es) if(l>p-1) np=min(np,r);
        if(np==_inf) break;
        ++ans;p=np;
    }
    cout<<ans<<'\n';
    return 0;
}
