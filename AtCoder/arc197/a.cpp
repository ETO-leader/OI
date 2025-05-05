#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int h,w;cin>>h>>w;
        string s;cin>>s;
        auto play=[&](string s){
            vector<int> mx(w),mn(w,h);
            auto x=h,y=0;
            for(auto&i:s){
                mx[y]=max(mx[y],x);
                mn[y]=min(mn[y],x);
                if(i=='D') --x;
                else ++y;
            }
            mx[y]=max(mx[y],x);
            mn[y]=min(mn[y],x);
            return pair(mx,mn);
        };
        auto dw=s;
        auto uh=h-1-ranges::count(s,'D');
        for(auto&i:dw) if(i=='?'){
            if(uh) i='D',--uh;
            else i='R';
        }
        auto rg=s;
        auto ur=w-1-ranges::count(s,'R');
        for(auto&i:rg) if(i=='?'){
            if(ur) i='R',--ur;
            else i='D';
        }
        const auto mn=play(dw).second;
        const auto mx=play(rg).first;
        auto ans=0ll;
        cir(i,0,w) ans+=(mx[i]-mn[i]+1);
        cout<<ans<<'\n';
    }();
    return 0;
}
