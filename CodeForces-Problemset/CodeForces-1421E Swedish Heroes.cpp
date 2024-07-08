#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
using arrs=array<array<lint,2>,2>;
const lint _inf=1e18+7;
const arrs mina=[](){
    arrs res;
    cir(i,0,2) cir(j,0,2) res[i][j]=-_inf;
    return res;
}();
auto&gmax(auto&a,auto b){
    return a=max(a,b);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    for(auto&i:a) cin>>i;
    vector<vector<arrs>> D(n,
        vector<arrs>(3,mina));
    if(n==1) exit(((cout<<a[0]<<'\n'),0));
    D[0][2][0][0]=-a[0];
    D[0][1][1][0]=a[0];
    cir(i,0,n-1) cir(j,0,3){
        cir(x,0,2) cir(y,0,2){
            auto&d=D[i][j][x][y];
            gmax(D[i+1][(j+1)%3][true][
                y||(x)],d+a[i+1]);
            gmax(D[i+1][(j+2)%3][false][
                y||(!x)],d-a[i+1]);
        }
    }
    cout<<max(D[n-1][1][0][1],
        D[n-1][1][1][1])<<'\n';
    return 0;
}
