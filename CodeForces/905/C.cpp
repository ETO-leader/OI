#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
using VI=vector<int>;
using lint=long long;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;VI a(n);
        map<int,int> id;
        for(auto&i:a) cin>>i,id.insert({i,0});
        [&](){
            int c=0;for(auto&[a,b]:id) b=c++;
        }();
        for(auto&i:a) i=id[i];
        rbt<int> rb;lint ans=0;
        VI cnx(n);
        cir(i,0,n) if((++cnx[a[i]])==1)
            rb.insert(i);
        fill(cnx.begin(),cnx.end(),0);
        for(int i=n-1;~i;--i){
            if((++cnx[a[i]])==1){
                ans+=rb.order_of_key(i+1);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
