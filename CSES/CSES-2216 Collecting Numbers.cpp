#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,xi,cnt=1;cin>>n;
    vector<int> rk(n);
    cir(i,0,n) cin>>xi,rk[xi-1]=i;
    cir(i,1,n) cnt+=rk[i]<rk[i-1];
    cout<<cnt<<'\n';
    return 0;
}