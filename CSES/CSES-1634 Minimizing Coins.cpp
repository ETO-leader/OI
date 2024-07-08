#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> c,D;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;c.resize(n);
    D.resize(x+1);
    for(auto&i:c) cin>>i;
    D[0]=1;
    cir(i,0,n) cir(j,c[i],x+1){
        D[j]=min(D[j],D[j-c[i]]+1);
    }
    cout<<D[x]<<'\n';
    return 0;
}