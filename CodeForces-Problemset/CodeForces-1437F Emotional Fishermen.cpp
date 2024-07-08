#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=998244353;
auto calculate_a(int n){
    vector<VI> res(n+1,VI(n+1,1));
    cir(i,0,n+1){
        lint usx=1;
        cir(j,0,i)
            (usx*=(i-j))%=MOD,res[i][j+1]=usx;
    }
    return res;
}
auto calculate_l(int n,VI&v){
    VI res(n);
    cir(i,0,n) res[i]=upper_bound(
        v.begin(),v.end(),v[i]/2)-v.begin();
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI v(n);
    for(auto&i:v) cin>>i;
    sort(v.begin(),v.end());
    VI D(n+1);D[0]=1;
    auto A=calculate_a(n);
    auto l=calculate_l(n,v);
    l.insert(l.begin(),-1);
    cir(i,1,n+1){
        D[i]=[&](){
            lint cnx=0;
            cir(j,0,l[i]+1){
                assert(n-2-l[j]>=0);
                (cnx+=D[j]*A[n-2-l[j]][
                    l[i]-l[j]-1])%=MOD;
            }
            return cnx;
        }();
        //cout<<i+1<<' '<<D[i]<<'\n';
    }
    cout<<(l[n]==n-1)*D[n]<<'\n';
    return 0;
}
