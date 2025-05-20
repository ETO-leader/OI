#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<int> x,y;
        rbt<int,greater<int>> qx,qy; 
        cir(i,0,n) (i&1?y:x).emplace_back(a[i]);
        vector<int> pos(n);
        cir(i,0,n) pos[a[i]-1]=i;
        auto cx=0ll;
        for(auto&i:x){
            cx+=qx.order_of_key(i);
            qx.insert(i);
        }
        auto cy=0ll;
        for(auto&i:y){
            cy+=qy.order_of_key(i);
            qy.insert(i);
        }
        ranges::sort(x);
        ranges::sort(y);
        if((cx&1)!=(cy&1)){
            if(n&1) swap(x[x.size()-1],x[x.size()-2]);
            else swap(y[y.size()-1],y[y.size()-2]);
        }
        vector<int> ans;
        cir(i,0,(int)(x.size())){
            ans.emplace_back(x[i]);
            if(i<(int)(y.size())) ans.emplace_back(y[i]);
        }
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
