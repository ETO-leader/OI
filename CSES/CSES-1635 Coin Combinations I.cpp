#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;vector<int> v(n),D(x+1);
    for(auto&i:v) cin>>i;D[0]=1;
    cir(i,1,x+1) for(auto&j:v) if(j<=i)
        (D[i]+=D[i-j])%=MOD;
    cout<<D[x]<<'\n';
    return 0;
}