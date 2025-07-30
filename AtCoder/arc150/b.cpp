#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint a,b;cin>>a>>b;
        if(b<a) return cout<<a-b<<'\n',void();
        auto ans=min(a*((b-1)/a+1)-b,b-a);
        for(auto v=a+1,r=-1ll;v<b;v=r+1){
            const auto x=(b-1)/v;
            r=(b-1)/x;
            ans=min(ans,(v-a)+(v*(x+1)-b));
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
