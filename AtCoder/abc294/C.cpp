#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;rbt<int> rb;
    vector<int> va(n),vb(m);
    for(auto&i:va) cin>>i,rb.insert(i);
    for(auto&i:vb) cin>>i,rb.insert(i);
    for(auto&i:va) cout<<rb.order_of_key(i)+1<<' ';
    cout<<'\n';
    for(auto&i:vb) cout<<rb.order_of_key(i)+1<<' ';
    cout<<'\n';
    return 0;
}
