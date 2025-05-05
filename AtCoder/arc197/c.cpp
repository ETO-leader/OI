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
static constexpr auto limb=(int)(1e5+7);
static constexpr auto lim=(int)(4e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    rbt<int,less<int>> tr;
    cir(i,1,limb) tr.insert(i);
    vector<int> ban(lim);
    unordered_set<int> apr;
    auto cur=limb;
    while(T--) [&]{
        int a,b;cin>>a>>b;
        if(!apr.contains(a)){
            apr.emplace(a);
            for(auto w=a;w<lim;w+=a) if(!ban[w]){
                ban[w]=true;
                if(w<cur+1) tr.erase(tr.upper_bound(w-1));
            }
        }
        while((int)(tr.size())<b){
            if(!ban[cur]) tr.insert(cur);
            ++cur;
        }
        cout<<*tr.find_by_order(b-1)<<'\n';
    }();
    return 0;
}
