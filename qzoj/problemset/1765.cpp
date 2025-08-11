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
    int n;cin>>n;
    rbt<int,less_equal<int>> rb;
    rb.insert(numeric_limits<int>::min());
    rb.insert(numeric_limits<int>::max());
    cir(i,0,n){
        int op,x;cin>>op>>x;
        if(op==1){
            rb.insert(x*2);
        }else if(op==2){
            rb.erase(rb.find_by_order(rb.order_of_key(x*2)));
        }else if(op==3){
            cout<<rb.order_of_key(x*2)<<'\n';
        }else if(op==4){
            cout<<*rb.find_by_order(x)/2<<'\n';
        }else if(op==5){
            cout<<*rb.find_by_order(rb.order_of_key(x*2)-1)/2<<'\n';
        }else if(op==6){
            cout<<*rb.find_by_order(rb.order_of_key(x*2+1))/2<<'\n';
        }
    }
    return 0;
}
