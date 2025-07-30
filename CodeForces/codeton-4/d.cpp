#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        auto l=1ll,r=(lint)(1e18l);
        cir(i,0,n){
            int op;cin>>op;
            if(op==1){
                lint a,b,n;cin>>a>>b>>n;
                const auto nl=(n-1?(a-b)*(n-2)+a+1:1),nr=(a-b)*(n-1)+a;
                if(nr<l||r<nl||nl>nr) cout<<0<<' ';
                else l=max(l,nl),r=min(r,nr),cout<<1<<' ';
            }else{
                lint a,b;cin>>a>>b;
                const auto cl=max((l-a+(a-b)-1)/(a-b),0ll);
                const auto cr=max((r-a+(a-b)-1)/(a-b),0ll);
                cout<<((cl==cr)?cl+1:-1)<<' ';
            }
        }
        cout<<'\n';
    }();
    return 0;
}
