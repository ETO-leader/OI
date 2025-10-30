#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,k;lint m;cin>>n>>m>>k;
        vector<lint> a(n);
        for(auto&x:a) cin>>x;
        ranges::sort(a);
        auto ans=make_pair(-1ll,-1ll);
        auto calc=[&](lint w){
            const auto wu=ranges::upper_bound(a,w)-a.begin()-1;
            const auto wv=ranges::lower_bound(a,w)-a.begin();
            auto wl=(wu-k+1>-1?(a[wu-k+1]+w)/2+1:0);
            auto wr=(wv+k-1<n?(a[wv+k-1]-1+w)/2:m);
            const auto uans=max<lint>(wr-wl+1,0);
            ans=max(ans,pair(uans,-w));
        };
        calc(0);calc(m);
        if(m) calc(1),calc(m-1);
        for(auto&x:a){
            cir(c,-2,3) if(x+c>-1&&x+c<m+1) calc(x+c);
        }
        cout<<ans.first<<' '<<-ans.second<<'\n';
    }();
    return 0;
}
