#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp=less<_Ty>>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    rbt<int,greater_equal<int>> tr;
    auto ans=0ll;
    for(auto&x:a){
        ans+=tr.order_of_key(x);
        tr.insert(x);
    }
    cout<<ans<<'\n';
    return 0;
}
