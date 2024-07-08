#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<int> p(n);
        for(auto&i:p) cin>>i;
        int mn=n+1,cnx=0;
        rbt<int> r1,r2;
        for(auto&i:p){
            r2.insert(i);
            if(i<mn){
                mn=i;r1.insert(i);
                continue;
            }
            cnx+=(r1.order_of_key(i)
                ==r2.order_of_key(i));
        }
        cout<<cnx<<'\n';
    }
    return 0;
}
