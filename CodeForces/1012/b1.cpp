#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        vector<int> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        stack<pair<int*,int>> stc;
        auto ans=1;
        cir(i,0,n*2){
            auto&ax=a[i%n],&bx=b[i%n];
            if(ax) stc.emplace(&ax,i);
            while((!stc.empty())&&bx>*stc.top().first-1){
                bx-=*stc.top().first;
                ans=max(ans,i-stc.top().second+1);
                *stc.top().first=0;
                stc.pop();
            }
            if(!stc.empty()) *stc.top().first-=bx,bx=0;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
