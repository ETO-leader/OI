#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int MOD=998244353;
int runx(VI&v,int cnx){
    vector<vector<VI>> D(v.size(),
        vector<VI>(cnx+1,VI(cnx)));
    D[0][0][0]=D[0][1][v[0]%cnx]=1;
    cir(i,0,v.size()-1) cir(j,0,cnx+1){
        cir(k,0,cnx){
            (D[i+1][j][k]+=D[i][j][k])%=MOD;
            if(j<cnx) (D[i+1][j+1][
                (k+v[i+1])%cnx]+=D[i][j][k])%=MOD;
        }
    }
    return D[v.size()-1][cnx][0];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI v(n);
    for(auto&i:v) cin>>i;
    int ans=0;
    cir(i,1,n+1) (ans+=runx(v,i))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
