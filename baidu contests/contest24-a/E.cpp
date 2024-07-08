#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto chkmin(vector<lint>&a){
    auto res=0ll;
    if(a.empty()) return res;
    if(a.size()==1) return a[0];
    sort(a.begin(),a.end());
    res=a.front();
    for(auto&i:a) res+=i;
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        vector<lint> pos,neg;
        auto cntz=0;
        for(auto&i:a){
            if(i>0) pos.push_back(-i);
            else if(i<0) neg.push_back(i);
            else ++cntz;
        }
        sort(pos.begin(),pos.end());
        sort(neg.begin(),neg.end());
        if(n==1){
            cout<<0<<'\n';
            return;
        }
        if(pos.empty()&&neg.empty()){
            cout<<0<<'\n';
            return;
        }
        if(neg.empty()){
            cir(i,0,cntz) pos.push_back(0);
            sort(pos.begin(),pos.end());
            auto ans=(pos.size()>2?-pos.front():0ll);
            for(auto&i:pos) ans-=i;
            cout<<ans+*max_element(pos.begin(),pos.end())*(1+(pos.size()>2))<<'\n';
            return;
        }
        if(pos.empty()){
            cir(i,0,cntz) neg.push_back(0);
            sort(neg.begin(),neg.end());
            auto ans=(neg.size()>2?-neg.front():0ll);
            for(auto&i:neg) ans-=i;
            cout<<ans+*max_element(neg.begin(),neg.end())*(1+(neg.size()>2))<<'\n';
            return;
        }
        const auto wx=pos.back(),wy=neg.back();
        pos.pop_back();neg.pop_back();
        auto ans=0ll;
        cir(spx,0,2) cir(spy,0,2) cir(lz,0,2) cir(rz,0,2){
            auto cl=pos;
            auto cr=neg;
            if(!spx) cl.push_back(wx);
            else cr.push_back(-wx);
            if(!spy) cl.push_back(-wy);
            else cr.push_back(wy);
            if(lz+rz>cntz) continue;
            if(lz) cl.push_back(0);
            if(rz) cr.push_back(0);
            const auto ansa=-chkmin(cl);
            const auto ansb=-chkmin(cr);
            if(cr.empty()){
                auto ansi=(cl.size()>2?-cl.front():0ll);
                for(auto&i:cl) ansi-=i;
                ans=max(ans,ansi+*max_element(cl.begin(),cl.end())*(1+(cl.size()>2)));
                continue;
            }
            if(cl.empty()){
                auto ansi=(cr.size()>2?-cr.front():0ll);
                for(auto&i:cr) ansi-=i;
                ans=max(ans,ansi+*max_element(cr.begin(),cr.end())*(1+(cr.size()>2)));
                continue;
            }
            ans=max(ans,ansa+ansb);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
