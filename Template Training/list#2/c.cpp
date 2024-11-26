#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int> a(n),b(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    vector<int> las(n);
    stack<int> stc;
    cir(i,0,n){
        while((!stc.empty())&&(a[stc.top()]==a[i]||b[stc.top()]<b[i]+1)) stc.pop();
        las[i]=(stc.empty()?-1:stc.top());
        stc.push(i);
    }
    vector<vector<pair<int,int>>> qx(n);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l;--r;
        qx[r].emplace_back(l,i);
    }
    vector<int> ans(q);
    rbt<int,less_equal<int>> rb;
    cir(i,0,n){
        rb.insert(las[i]);
        for(auto&[l,id]:qx[i]) ans[id]=rb.order_of_key(l)-l;
    }
    ranges::copy(ans,ostream_iterator<int>(cout,"\n"));
    return 0;
}
