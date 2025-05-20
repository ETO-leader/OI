#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp=less<_Ty>>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
static constexpr auto maxsc=650;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    auto cnt=0ll;
    for(auto l=0,r=0;l<n;l=(++r)){
        while(r+1<n&&a[r+1]<a[r]) ++r;
        if(r>l){
            ++cnt;
            reverse(a.begin()+l,a.begin()+r+1);
        }
    }
    rbt<int,greater<int>> rb;
    for(auto&i:a) cnt+=rb.order_of_key(i),rb.insert(i);
    cout<<cnt<<'\n';
    return 0;
}
