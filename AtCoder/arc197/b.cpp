#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
static constexpr auto eps=1e-8l;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        ranges::sort(a,greater<int>());
        rbt<lf,less_equal<lf>> cur(a.begin(),a.end());
        auto sum=accumulate(a.begin(),a.end(),0.0l);
        auto ans=0,cnt=n;
        for(auto&i:a){
            const auto avg=sum/cnt;
            ans=max<int>(ans,cnt-cur.order_of_key(avg+eps));
            cur.erase(cur.upper_bound(i-eps));
            sum-=i;--cnt;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
