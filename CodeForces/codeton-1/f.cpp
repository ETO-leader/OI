#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        ranges::sort(a);
        const auto liml=a[0]-7;
        const auto limr=a[n-1]+7;
        auto check=[&](lint t){
            const auto lw=a[0]+t,rw=a[n-1]+t;
            auto res=0ll;
            if(rw>0){
                cir(i,1,n) res+=(a[i]+t>0?lw:rw)*(a[i]+t)-t*t;
            }else{
                cir(i,0,n-1) res+=(a[i]+t>0?lw:rw)*(a[i]+t)-t*t;
            }
            return res;
        };
        const auto ckz=check(0);
        if(check(liml)<check(liml-1)) return cout<<"INF"<<'\n',void();
        if(check(limr)<check(limr+1)) return cout<<"INF"<<'\n',void();
        auto l=liml-7,r=limr+7;
        while(r-l+1>5){
            const auto lmid=l+(r-l+1)/3;
            const auto rmid=l+(r-l+1)/3*2;
            const auto lw=check(lmid);
            const auto rw=check(rmid);
            if(lw<rw) l=lmid;
            else r=rmid;
        }
        auto ansp=l,answ=check(ansp);
        cir(i,l+1,r+1) if(const auto uw=check(i);uw>answ){
            ansp=i;answ=uw;
        }
        cout<<answ<<'\n'; 
    }();
    return 0;
}
