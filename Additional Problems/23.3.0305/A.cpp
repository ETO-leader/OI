#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<int> v(n);
    for(auto&i:v) cin>>i;
    sort(v.begin(),v.end());
    if([&](){
        cir(i,1,n) if(v[i]>v[i-1]+1)
            return false;
        return true;
    }()){cout<<0<<'\n';exit(0);}
    auto rundp=[&](lint d0=0){
        vector<lint> D(n);D[0]=d0+v[0];
        cir(i,1,n)
            D[i]=(v[i]<=v[i-1]+1?D[i-1]:0)+v[i];
        return D;
    };
    auto D=rundp(((m==(*max_element(v.begin()
        ,v.end()))+1)&&(!v[0]))?rundp()[n-1]:0);
    cout<<accumulate(v.begin(),v.end(),0LL)-
        *max_element(D.begin(),D.end())<<'\n';
    return 0;
}
