#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<vector<int>> c(n);
        cir(i,0,n) c[a[i]-1].emplace_back(i);
        auto check=[&](int k){
            vector<int> ers(n);
            priority_queue<int> mxp;
            priority_queue<int,vector<int>,greater<int>> mnp;
            auto res=0ll;
            cir(i,0,n) if(a[i]>k) mxp.emplace(i),mnp.emplace(i);
            for(auto i=k-1;~i;--i){
                for(auto&u:c[i]) mxp.emplace(u),mnp.emplace(u);
                while((!mxp.empty())&&ers[mxp.top()]) mxp.pop();
                while((!mnp.empty())&&ers[mnp.top()]) mnp.pop();
                if(mxp.empty()||mnp.empty()||mxp.top()==mnp.top()){
                    return -1ll;
                }else{
                    res+=mxp.top()-mnp.top();
                    ers[mxp.top()]=true;
                    ers[mnp.top()]=true;
                }
            }
            return res;
        };
        auto l=0,r=n/2;
        while(l+5<r){
            const auto lm=l+(r-l)/3,rm=l+(r-l)/3*2;
            const auto lw=check(lm);
            const auto rw=check(rm);
            if(lw>rw-1) r=rm;
            else l=lm;
        }
        auto ans=0ll;
        cir(i,l,r+1) ans=max(ans,check(i));
        cout<<ans<<'\n';
    }();
    return 0;
}
