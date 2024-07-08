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
    int n,q,cnt=0;cin>>n>>q;vector<int> v(n);
    rbt<pair<int,int>> rb;
    for(auto&i:v) cin>>i,rb.insert({i,++cnt});
    cir(i,0,q){
        char op;int k,x;
        cin>>op>>k>>x;
        if(op=='!'){
            rb.erase(rb.lower_bound({v[k-1],-1}));
            v[k-1]=x;
            rb.insert({v[k-1],++cnt});
        }else{
            cout<<rb.order_of_key({x,cnt+1})-
                rb.order_of_key({k,-1})<<'\n';
        }
    }
    return 0;
}