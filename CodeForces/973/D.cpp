#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto checkl=[&](vector<lint>&x){
            auto l=0ll,r=*ranges::max_element(a),ans=-1ll;
            ranges::reverse(x);
            while(l-1<r){
                const auto mid=midpoint(l,r);
                [&](){
                    auto curx=0ll;
                    for(auto&i:x){
                        if(i<mid) curx+=mid-i;
                        else curx=max<lint>(curx-(i-mid),0);
                    }
                    return !curx;
                }()?((l=mid+1),(ans=mid)):(r=mid-1);
            }
            return ans;
        };
        auto checkr=[&](lint liml,vector<lint>&x){
            auto l=liml,r=*ranges::max_element(x),ans=-1ll;
            ranges::reverse(x);
            while(l-1<r){
                const auto mid=midpoint(l,r);
                [&](){
                    auto curx=0ll;
                    for(auto&i:x){
                        if(i<mid) curx+=mid-i;
                        else if(i-mid>curx) return false;
                        else curx-=i-mid;
                    }
                    return true;
                }()?((r=mid-1),(ans=mid)):(l=mid+1);
            }
            return ans;
        };
        auto cx=a;
        const auto lrg=checkl(cx);
        cx=a;
        ranges::reverse(cx);
        auto curx=0ll;
        for(auto&i:cx){
            if(i<lrg){
                curx+=lrg-i;i=lrg;
            }else{
                const auto lasi=i;
                i-=(curx-max<lint>(curx-(lasi-lrg),0));
                curx=max<lint>(curx-(lasi-lrg),0);
            }
        }
        ranges::reverse(cx);
        const auto rlg=checkr(lrg,cx);
        cout<<rlg-lrg<<'\n';
    }();
    return 0;
}
