#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using rbt=tree<T,null_type,less<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;rbt<int> rb;
    int order=0;
    cir(i,1,n+1) rb.insert(i);
    cir(i,0,n){
        (order+=k)%=rb.size();
        cout<<*rb.find_by_order(order)<<' ';
        rb.erase(rb.find_by_order(order));
    }
    cout<<'\n';
    return 0;
}
