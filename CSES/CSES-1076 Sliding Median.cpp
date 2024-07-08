#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
using PI=pair<int,int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,cnt=0,xi;cin>>n>>k;
    rbt<PI> rb;queue<int> q;
    cir(i,0,k) cin>>xi,rb.insert({xi,++cnt}),q.push(xi);
    cout<<rb.find_by_order((k-1)/2)->first<<' ';
    cir(i,k,n){
        cin>>xi;q.push(xi);rb.insert({xi,++cnt});
        rb.erase(rb.lower_bound({q.front(),-1}));q.pop();
        cout<<rb.find_by_order((k-1)/2)->first<<' ';
    }
    cout<<'\n';
    return 0;
}