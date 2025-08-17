#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<lint> a(1<<n);
    for(auto&i:a) cin>>i;
    vector<vector<int>> op(n);
    cir(i,0,q){
        int x,y;cin>>x>>y;op[x].emplace_back(y);
    }
    cir(i,0,n){
        auto vz=complex<lint>(1,0),vy=complex<lint>(0,1);
        auto ensure=[&]{
            vz=complex<lint>(real(vz)%MOD,imag(vz)%MOD);
            vy=complex<lint>(real(vy)%MOD,imag(vy)%MOD);
        };
        for(auto&y:op[i]){
            if(!y) vy+=vz;
            else vz+=vy;
            ensure();
        }
        const auto la=a;
        cir(w,0,(1<<n)){
            if((w>>i)&1){
                a[w]=(la[w]*imag(vy)+la[w^(1<<i)]*real(vy))%MOD;
            }else{
                a[w]=(la[w]*real(vz)+la[w^(1<<i)]*imag(vz))%MOD;
            }
        }
    }
    for(auto&i:a) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
