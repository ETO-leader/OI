#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
const int max_t=1e9+7;
struct cat{lint p,v;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<cat> c(n);
    for(auto&[p,v]:c) cin>>p>>v;
    sort(c.begin(),c.end(),[](cat&a,cat&b){
        return a.p==b.p?a.v>b.v:a.p<b.p;
    });
    reverse(c.begin(),c.end());
    lint minp=_inf,cnx=0,mx=0;
    for(auto&[p,v]:c){
        const auto pos=p+v*max_t;
        if(pos<minp){
            mx=max(mx,cnx);cnx=1;
            minp=pos;
        }else{
            ++cnx;
        }
    }
    cout<<max(mx,cnx)<<'\n';
    return 0;
}