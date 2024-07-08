#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
auto gauss(vector<VI>&a,const int p){
    const int n=a.size();
    lint res=1;
    auto modminus=[p](lint&a,lint b){
        a=(a%p-b%p+p)%p;
    };
    cir(i,0,n) cir(j,i+1,n){
        auto swapi=[&](){
            swap(a[i],a[j]);res=-res;
        };
        while(a[i][i]){
            const auto x=a[j][i]/a[i][i];
            cir(k,i,n)
                modminus(a[j][k],x*a[i][k]);
            swapi();
        }
        swapi();
    }
    cir(i,0,n) (res*=a[i][i])%=p;
    return (res+p)%p;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,p;cin>>n>>p;
    vector<VI> mat(n,VI(n));
    for(auto&i:mat) for(auto&j:i) cin>>j;
    cout<<gauss(mat,p)<<'\n';
    return 0;
}
