#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;string s;cin>>s;
        auto ans=0ll;
        vector<lint> failed;
        cir(i,0,n) if(s[i]=='0') failed.push_back(i+1);
        vector<lint> flx;
        for(auto i=n-1;~i;--i) if(s[i]=='1'){
            while((!failed.empty())&&failed.back()>i+1) ans+=failed.back(),failed.pop_back();
            if(!failed.empty()) ans+=failed.back(),failed.pop_back();
            else flx.push_back(i+1);
            // clog<<i<<":"<<ans<<'\n';
        }
        for(auto&i:failed) ans+=i;
        ranges::sort(flx);
        // clog<<flx.size()<<' '<<ans<<' '<<flx[0]<<'\n';
        cir(i,0,(int)(flx.size()+1)/2) ans+=flx[i];
        // clog<<ans<<'\n';
        println("{}",ans);
    }();
    return 0;
}
