#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;cin>>t;
    int ac;cin>>ac;
    vector<pair<int,int>> a(ac);
    for(auto&[x,y]:a) cin>>x>>y;
    int bc;cin>>bc;
    vector<pair<int,int>> b(bc);
    for(auto&[x,y]:b) cin>>x>>y;
    auto count=[&](const int ut,vector<pair<int,int>>&c){
        auto ans=0ll;
        for(auto&[x,y]:c) if(ut>x-1) ans+=(ut-x)/y+1;
        return ans;
    };
    auto l=0,r=t;
    while(l+1<r){
        const auto mid=(l+r)/2;
        count(mid,a)>count(t-mid,b)?r=mid:l=mid;
    }
    cout<<l<<'\n';
    return 0;
}
