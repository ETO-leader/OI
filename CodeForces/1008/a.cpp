#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;n*=2;
        vector<lint> b(n);
        for(auto&i:b) cin>>i;
        ranges::sort(b);
        vector<lint> a;
        auto pl=0,pr=n-2;
        a.emplace_back(b[n-1]);
        cir(i,1,n) if(!(i&1)){
            a.emplace_back(b[pl]);++pl;
        }else{
            a.emplace_back(b[pr]);--pr;
        }
        auto x=0ll;
        cir(i,1,n) x+=(a[i]*(i&1?-1:1));
        const auto w=a[0]-x;
        a.emplace(a.begin()+1,w);
        for(auto&i:a) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
