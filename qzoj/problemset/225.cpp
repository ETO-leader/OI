#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&x:a) cin>>x;
    vector<int> f(n);
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    sort(p.begin(),p.end(),[&](auto u,auto v){
        return u==v?u<v:a[u]<a[v];
    });
    vector<int> cur;
    for(auto&x:p){
        auto mx=0;
        for(auto&p:cur) if(!(a[x]%a[p])) mx=max(mx,f[p]);
        f[x]=mx+1;
        cur.emplace_back(x);
    }
    cout<<*max_element(f.begin(),f.end())<<'\n';
    return 0;
}
