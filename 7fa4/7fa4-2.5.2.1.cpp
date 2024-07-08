#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
using lint=long long;
template<typename T>
using Tree=tree<T,null_type,greater<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,ans=0;cin>>n;Tree<lint> Tr;
    cir(i,0,n){
        lint vi;cin>>vi;
        ans+=Tr.order_of_key(vi);
        Tr.insert(vi);
    }
    cout<<ans<<endl;
    return 0;
}