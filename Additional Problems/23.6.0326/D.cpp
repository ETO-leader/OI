#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VL=vector<lint>;
const int MOD=998244353;
auto C=[](){
    const int n=5007;
    vector<VL> res(n,VL(n));
    cir(i,0,n) res[0][i]=1;
    cir(i,1,n) cir(j,1,n){
        res[i][j]=res[i][j-1];
        (res[i][j]+=res[i-1][j-1])%=MOD;
    }
    return res;
}();
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;const int n=s.size();
    VL cx(26);for(auto&i:s) cx[i-'a']++;
    vector<VL> D(26,VL(n+1));
    cir(i,0,cx[0]+1) D[0][i]=1;
    cir(i,1,26) cir(w,0,n+1){
        cir(x,0,min<int>(w,cx[i])+1){
            (D[i][w]+=D[i-1][w-x]*C[x][w])%=MOD;
        }
    }
    cout<<accumulate(D[25].begin()+1,D[25].end(),0LL,
        [](lint a,lint b){return (a+b)%MOD;})<<'\n';
    return 0;
}
