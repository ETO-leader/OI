#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> D(n+1);
    D[0]=1;
    cir(i,1,n+1){
        cir(j,max(i-6,0),i) (D[i]+=D[j])%=MOD;
    }
    cout<<D[n]<<'\n';
    return 0;
}