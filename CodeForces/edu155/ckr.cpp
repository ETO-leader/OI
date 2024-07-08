#include<bits/stdc++.h>
#define int long long
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<int> a(n),prx(n);
    for(auto&i:a) cin>>i;
    prx[0]=a[0];
    cir(i,1,n) prx[i]=a[i]^prx[i-1];
    int cnx=0;
    cir(i,0,n) cir(j,i,n){
        int xr=(prx[j]^(i?prx[i-1]:0));
        (cnx+=xr*(j-i+1))%=998244353;
    }
    cout<<cnx<<'\n';
    return 0;
}
