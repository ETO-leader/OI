#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;lint m;cin>>n>>m;
    vector<tuple<lint,lint,lint,lint,lint,lint>> x(n);
    for(auto&[a,b,sm,pm,sv,pv]:x) cin>>a>>b>>sm>>pm>>sv>>pv;
    auto check=[&](const int q){
        auto cost=1ll;
        for(auto&[a,b,sm,pm,sv,pv]:x){
            auto costu=m+7;
            cir(c,0,2000){
                const auto lst=max(a*q-b-sm*c,0ll);
                costu=min(costu,c*pm+(lst+sv-1)/sv*pv);
            }
            cir(c,0,2000){
                const auto lst=max(a*q-b-sv*c,0ll);
                costu=min(costu,c*pv+(lst+sm-1)/sm*pm);
            }
            cost+=costu;
            if(cost>m+1) return false;
        }
        return true;
    };
    auto l=0,r=(int)(5e6),ans=-1;
    while(l-1<r){
        const auto mid=(l+r)/2;
        check(mid)?((l=mid+1),(ans=mid)):(r=mid-1);
    }
    cout<<ans<<'\n';
    return 0;
}
