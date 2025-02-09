#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxb=30;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        string a,b;cin>>a>>b;
        const auto n=(int)(a.size());
        vector<int> c(n+1);
        cir(i,1,n+1) c[i]=c[i-1]+a[i-1]-b[i-1];
        if(c[n]) return cout<<"-1"<<'\n',void();
        auto las=0;
        cir(i,1,n+1) if(!c[i]){
            if(las<i-1){
                auto cnt=0;
                cir(p,las+1,i) cnt+=b[p]!=b[p-1];
                if(cnt!=1) return cout<<"-1"<<'\n',void();
                if(i<n&&(b[i]!=b[i-1]||a[i]==a[i-1])) return cout<<"-1"<<'\n',void();
                if(las&&(b[las]!=b[las-1]||a[las]==a[las-1])) return cout<<"-1"<<'\n',void();
            }
            las=i;
        }
        auto ans=(int)(a.front()!=b.front())+(int)(a.back()!=b.back());
        cir(i,1,n) ans+=(int)(a[i]!=a[i-1])-(int)(b[i]!=b[i-1]);
        cout<<ans/2<<'\n';
    }();
    return 0;
}
