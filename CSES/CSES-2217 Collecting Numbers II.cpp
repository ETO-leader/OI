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
    int n,m,cnt=0;cin>>n>>m;
    rbt<pair<int,int>> rb;
    auto del=[&rb](int x){rb.erase(rb.upper_bound({x,0}));};
    auto ins=[&rb,&cnt](int x){rb.insert({x,(++cnt)});};
    vector<int> rk(n+2),ve(n+1);rk[n+1]=n+1;
    cir(i,0,n) cin>>ve[i+1],rk[ve[i+1]]=i+1;
    cir(i,1,n+2) ins(rk[i]-rk[i-1]);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        int r1=rk[ve[u]]-rk[ve[u]-1],r2=rk[ve[u]+1]-rk[ve[u]];
        del(r1);del(r2);
        r1=rk[ve[v]]-rk[ve[v]-1],r2=rk[ve[v]+1]-rk[ve[v]];
        del(r1);del(r2);
        swap(rk[ve[u]],rk[ve[v]]);swap(ve[u],ve[v]);
        ins(rk[ve[u]]-rk[ve[u]-1]);ins(rk[ve[u]+1]-rk[ve[v]]);
        ins(rk[ve[v]]-rk[ve[v]-1]);
        ins(rk[ve[v]+1]-rk[ve[v]]);
        cout<<rb.order_of_key({0,0})+1<<'\n';
        cir(i,1,n+1) cout<<ve[i]<<' ';
        cout<<'\n';
        for(auto&i:rk) cout<<i<<' ';
        cout<<'\n';
        for(auto i:rb) cout<<i.first<<' ';
        cout<<"\n\n";
    }
    return 0;
}