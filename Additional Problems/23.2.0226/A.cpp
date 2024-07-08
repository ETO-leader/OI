#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using bst=tree<T,null_type,less_equal<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,q;cin>>n>>q;
    bst<lint> rbt;
    cir(i,0,n){
        lint k;cin>>k;rbt.insert(k);
    }
    vector<lint> vx;lint cnx=0;
    vector<lint> vc;
    for(auto i:rbt) cnx+=i,vx.push_back(cnx);
    cir(i,0,q){
        lint x;cin>>x;
        if(x>=(*(--rbt.end()))){
            cout<<x*n-vx.back()<<'\n';continue;
        }
        if(x<=(*rbt.begin())){
            cout<<vx.back()-(x*n)<<'\n';continue;
        }
        auto nx=rbt.order_of_key(x);--nx;
        cout<<(x*(nx+1)-vx[nx])+
            (vx[n-1]-vx[nx]-x*(n-nx-1))<<'\n';
    }
    return 0;
}
