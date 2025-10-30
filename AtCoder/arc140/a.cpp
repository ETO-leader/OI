#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;string s;cin>>n>>k>>s;
    auto ans=n;
    cir(l,1,n+1) if((!(n%l))){
        vector<map<char,int>> cnt(l);
        cir(i,0,n) ++cnt[i%l][s[i]];
        auto cx=n/l;
        auto cur=0ll;
        for(auto&x:cnt){
            auto mn=cx;
            for(auto&[a,b]:x) mn=min(mn,cx-b);
            cur+=mn;
        }
        if(cur<k+1) ans=min(ans,l);
    }
    cout<<ans<<'\n';
    return 0;
}
