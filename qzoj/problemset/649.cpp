#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
};
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    const auto sqr=(int)(n/sqrt(q)+1);
    vector<tuple<int,int,int,int>> qry(q);
    auto c=-1;
    for(auto&[l,r,k,id]:qry) cin>>l>>r>>k,--l,--r,id=++c;
    sort(qry.begin(),qry.end(),[&](auto&a,auto&b){
        return get<0>(a)/sqr==get<0>(b)/sqr?get<1>(a)<get<1>(b):get<0>(a)<get<0>(b);
    });
    vector<int> ans(q);
    rbt<int,less_equal<int>> rb;
    auto l=0,r=-1;
    for(auto&[ql,qr,k,id]:qry){
        while(r<qr) rb.insert(a[++r]);
        while(ql<l) rb.insert(a[--l]); 
        while(qr<r) rb.erase(rb.find_by_order(rb.order_of_key(a[r]))),--r;
        while(l<ql) rb.erase(rb.find_by_order(rb.order_of_key(a[l]))),++l;
        ans[id]=*rb.find_by_order(k-1);
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
