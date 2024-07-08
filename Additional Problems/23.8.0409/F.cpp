#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,l;cin>>n>>k>>l;
    VI ar(n),lp(k),sgm(n+1,1);
    vector<VI> D(n+1,VI(k));
    for(auto&i:ar) cin>>i,--i;
    ar.insert(ar.begin(),114514);
    cir(i,1,n+1){
        cir(j,0,k){
            if(ar[i]==j||ar[i]<0)
                lp[j]++;
            else lp[j]=0;
        }
        cir(j,0,k){
            if(ar[i]>=0&&ar[i]!=j) continue;
            D[i][j]=sgm[i-1];
            if(lp[j]>=l){
                D[i][j]-=(sgm[i-l]-D[i-l][j]);
                (D[i][j]+=MOD)%=MOD;
            }
        }
        sgm[i]=accumulate(D[i].begin(),D[i].end(),
            0,[](int a,int b){return (a+b)%MOD;});
    }
    cout<<sgm[n]<<'\n';
    return 0;
}
