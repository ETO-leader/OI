#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
static constexpr auto maxa=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;rbt<int,less_equal<int>> rb;
    cir(i,0,n){
        int x;cin>>x;rb.insert(x);
        if(!(i&1)){
            const auto pless=i/2;
            auto l=0,r=maxa,ans=-1;
            while(l-1<r){
                const auto mid=midpoint(l,r);
                rb.order_of_key(mid)<pless+1?((l=mid+1),(ans=mid)):(r=mid-1);
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}
