#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto gauss(vector<vector<lint>> a,const auto p){
    auto res=1ll;
    auto minusm=[&](auto&x,auto b){
        return (x+=p-b)%=p;
    };
    const auto n=(int)(a.size());
    cir(i,0,n) cir(j,i+1,n){
        auto swapi=[&](){
            swap(a[i],a[j]);(res*=(p-1))%=p;
        };
        while(a[i][i]){
            const auto x=a[j][i]/a[i][i];
            cir(k,i,n) minusm(a[j][k],a[i][k]*x%p);
            swapi();
        }
        swapi();
    }
    cir(i,0,n) (res*=a[i][i])%=p;
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,p;cin>>n>>p;
    vector a(n,vector<lint>(n));
    for(auto&x:a) for(auto&i:x) cin>>i;
    cout<<gauss(a,p)<<'\n';
    return 0;
}
