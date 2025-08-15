#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint x,y,a,b,c,d;
        cin>>x>>y>>a>>b>>c>>d;
        auto ans=numeric_limits<lint>::max();
        if(x==y) ans=0;
        if((x&a)==y) ans=min(ans,c);
        if((x|b)==y) ans=min(ans,d);
        if(((x|b)&a)==y||((x&a)|b)==y) ans=min(ans,c+d);
        cout<<(ans<numeric_limits<lint>::max()?ans:-1)<<'\n';
    }();
    return 0;
}
