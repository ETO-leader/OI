#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=998244353;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
using lint=long long;
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<lint> cnt(n);
    rbt<int,less<int>> rb;
    for(auto i=n-1;~i;--i){
        cnt[i]=rb.order_of_key(a[i]);
        rb.insert(a[i]);
    }
    auto pre=cnt,suf=cnt;
    cir(i,1,n) (pre[i]+=pre[i-1])%=MOD;
    for(auto i=n-2;~i;--i) (suf[i]+=suf[i+1])%=MOD;
    suf.push_back(0);
    auto ans=0ll;
    const auto prob=math.inv(n-k+1);
    const auto psub=1ll*k*(k-1)%MOD*math.inv(4)%MOD;
    rbt<int,less<int>> rx;
    rbt<int,greater<int>> in;
    auto curw=0ll;
    cir(i,n-k,n) in.insert(a[i]);
    for(auto r=n-1;r>k-2;--r){
        const auto l=r-k+1;
        if(r<n-1){
            curw-=rx.order_of_key(a[r+1]);
            in.erase(in.find(a[r+1]));
            in.insert(a[l]);
            curw+=rx.order_of_key(a[l]);
            rx.insert(a[r+1]);
            curw+=in.order_of_key(a[r+1]);
        }
        (ans+=prob*(curw%MOD+(l?pre[l-1]:0)+suf[r+1]+psub))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
