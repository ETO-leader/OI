#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(auto a,auto b){
        auto res=(decltype(a))(1);
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow((lint)(x),MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,q;cin>>n>>q;vector<lint> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        auto ax=a,bx=b;
        ranges::sort(a);
        ranges::sort(b);
        auto ans=1ll;
        cir(i,0,n) (ans*=min(a[i],b[i]))%=MOD;
        print(cout,"{} ",ans);
        cir(i,0,q){
            int op,x;cin>>op>>x;--x;
            if(op==1){
                const auto w=ax[x];
                ++ax[x];
                auto p=ranges::lower_bound(a,w)-a.begin();
                auto nxtp=prev(ranges::lower_bound(a,w+1))-a.begin();
                (ans*=math.inv(min(a[p],b[p])))%=MOD;
                ++a[p];
                (ans*=min(a[p],b[p]))%=MOD;
                {
                    (ans*=math.inv(min(a[p],b[p])))%=MOD;
                    (ans*=math.inv(min(a[nxtp],b[nxtp])))%=MOD;
                    swap(a[p],a[nxtp]);
                    (ans*=(min(a[p],b[p])))%=MOD;
                    (ans*=(min(a[nxtp],b[nxtp])))%=MOD;
                }
            }else{
                const auto w=bx[x];
                ++bx[x];
                auto p=ranges::lower_bound(b,w)-b.begin();
                auto nxtp=prev(ranges::lower_bound(b,w+1))-b.begin();
                (ans*=math.inv(min(a[p],b[p])))%=MOD;
                ++b[p];
                (ans*=min(a[p],b[p]))%=MOD;
                {
                    (ans*=math.inv(min(a[p],b[p])))%=MOD;
                    (ans*=math.inv(min(a[nxtp],b[nxtp])))%=MOD;
                    swap(b[p],b[nxtp]);
                    (ans*=(min(a[p],b[p])))%=MOD;
                    (ans*=(min(a[nxtp],b[nxtp])))%=MOD;
                }
            }
            print(cout,"{} ",ans);
        }
        println(cout,"");
    }();
    return 0;
}
