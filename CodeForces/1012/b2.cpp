#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;lint k;cin>>n>>k;
        vector<int> ax(n),bx(n);
        for(auto&i:ax) cin>>i;
        for(auto&i:bx) cin>>i;
        auto check=[&](const int mid){
            auto a=ax,b=bx;
            auto kx=k;
            deque<pair<int*,int>> stc;
            auto ans=1;
            cir(i,0,n*3){
                auto&ax=a[i%n],&bx=b[i%n];
                if(ax) stc.emplace_back(&ax,i);
                while((!stc.empty())&&(i-stc.front().second+1>mid)){
                    kx-=*stc.front().first;
                    *stc.front().first=0;
                    stc.pop_front();
                }
                while((!stc.empty())&&bx>*stc.back().first-1){
                    bx-=*stc.back().first;
                    ans=max(ans,i-stc.back().second+1);
                    *stc.back().first=0;
                    stc.pop_back();
                }
                if(!stc.empty()) *stc.back().first-=bx,bx=0;
            }
            return kx>-1;
        };
        auto l=0,r=n,ans=n;
        while(l<r+1){
            const auto mid=(l+r)/2;
            check(mid)?((r=mid-1),(ans=mid)):(l=mid+1);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
