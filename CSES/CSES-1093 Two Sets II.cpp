#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint MOD=2e9+14;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,step=0,cnt=0;cin>>n;
    vector<vector<lint>> D(2,vector<lint>(n*n));
    D[0][0]=1;
    cir(i,0,n){
        step^=1;cnt+=(i+1);
        cir(j,0,n*n){
            if(j<=i) D[step][j]=D[step^1][j];
            else D[step][j]=(D[step^1][j-i-1]+D[step^1][j])%MOD;
        }
    }
    if(cnt&1) cout<<0<<'\n';
    else cout<<D[step][cnt/2]/2<<'\n';
    return 0;
}