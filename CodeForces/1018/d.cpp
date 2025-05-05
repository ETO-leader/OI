#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        auto ansx=0,anss=0;
        cir(i,0,n){
            int x,y;cin>>x>>y;
            ansx^=x;anss^=(x+y);
        }
        cout<<ansx<<' '<<anss-ansx<<'\n';
    }();
    return 0;
}
